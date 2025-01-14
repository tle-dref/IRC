// kick.cpp

#include "Client.hpp"
#include "Channel.hpp"
#include "Tokenisation.hpp"
#include <iostream>
#include <map>

// -----------------------------------------------------------------------------
// Validation de la commande KICK
// Format général: KICK <channel> <user> [<commentaire>...]
// -----------------------------------------------------------------------------
bool validateKick(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient) {
  // 1) Vérifier qu'il y a suffisamment d'arguments
  //    (au minimum le nom du channel et le pseudo à kicker)
  if (cmd.getArguments().size() < 2) {
    std::cerr << "error_461 : ERR_NEEDMOREPARAMS (KICK)" << std::endl;
    return false;
  }

  const std::string &channelName = cmd.getArguments()[0];
  const std::string &targetNick = cmd.getArguments()[1];

  // 2) Vérifier que le channel existe
  if (!channels.channelExists(channelName)) {
    std::cerr << "error_403 : ERR_NOSUCHCHANNEL (" << channelName << ")"
              << std::endl;
    return false;
  }

  // 3) Vérifier que l'utilisateur qui envoie KICK est dans le channel
  if (!channels.isUserInChannel(channelName, idClient)) {
    std::cerr << "error_442 : ERR_NOTONCHANNEL (Vous n'êtes pas dans "
              << channelName << ")" << std::endl;
    return false;
  }

  // 4) Vérifier que l'utilisateur est opérateur du channel (permission KICK)
  if (!channels.isOperator(channelName, idClient)) {
    std::cerr << "error_482 : ERR_CHANOPRIVSNEEDED (Pas d'op sur " << channelName
              << ")" << std::endl;
    return false;
  }

  // 5) Vérifier que la cible (targetNick) existe dans la liste des clients
  int targetId = -1;
  const std::map<int, Client> &allClients = clients.getClients();
  for (std::map<int, Client>::const_iterator it = allClients.begin();
       it != allClients.end(); ++it) {
    if (it->second.nickname == targetNick) {
      targetId = it->first;
      break;
    }
  }
  if (targetId == -1) {
    std::cerr << "error_401 : ERR_NOSUCHNICK (" << targetNick << ")"
              << std::endl;
    return false;
  }

  // 6) Vérifier que la cible se trouve bien sur le channel
  if (!channels.isUserInChannel(channelName, targetId)) {
    std::cerr << "error_441 : ERR_USERNOTINCHANNEL (" << targetNick << " @ "
              << channelName << ")" << std::endl;
    return false;
  }

  // Si toutes les vérifications passent, on considère la commande comme valide
  return true;
}

// -----------------------------------------------------------------------------
// Exécution de la commande KICK
// -----------------------------------------------------------------------------
void doKick(ClientManager clients, ChannelManager channels,
            const TokenisedCommand &cmd, const int idClient) {
  // On suppose que validateKick() est déjà passé avec succès
  const std::string &channelName = cmd.getArguments()[0];
  const std::string &targetNick = cmd.getArguments()[1];

  // Récupérer l'ID de la cible à partir du pseudo
  int targetId = -1;
  const std::map<int, Client> &allClients = clients.getClients();
  for (std::map<int, Client>::const_iterator it = allClients.begin();
       it != allClients.end(); ++it) {
    if (it->second.nickname == targetNick) {
      targetId = it->first;
      break;
    }
  }

  // Retirer la cible du channel
  // Le removeUser prend un objet Client en paramètre, donc on récupère le Client*
  Client *targetClient = clients.getClient(targetId);
  if (targetClient != NULL) {
    channels.removeUser(channelName, *targetClient);

    // Message de confirmation côté serveur
    std::cout << "L'utilisateur " << targetNick << " a été kick du channel "
              << channelName << " par "
              << clients.getClient(idClient)->nickname << std::endl;

    // Vous pouvez ici envoyer un message au client concerné,
    // ou à tous les membres du channel, etc.
    // Ex: clients.sendPrvMsg(targetClient, "Vous avez été expulsé de " + channelName);
  } else {
    // Normalement, on ne devrait pas arriver ici si validateKick a passé
    std::cerr << "Erreur interne : impossible de récupérer le client cible."
              << std::endl;
  }
}
