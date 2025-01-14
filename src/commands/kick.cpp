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
bool validateKick(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, const int idClient) {
    if (cmd.getArguments().size() < 2) {
        std::string response = "461 KICK :Not enough parameters\r\n";
        send(idClient, response.c_str(), response.length(), 0);
        return false;
    }

    std::string channelName = cmd.getArguments()[0];
    std::string targetNick = cmd.getArguments()[1];

    if (!channels.channelExists(channelName)) {
        std::string response = "403 " + channelName + " :No such channel\r\n";
        send(idClient, response.c_str(), response.length(), 0);
        return false;
    }

    if (!channels.isOperator(channelName, idClient)) {
        std::string response = "482 " + channelName + " :You're not channel operator\r\n";
        send(idClient, response.c_str(), response.length(), 0);
        return false;
    }

    int targetFd = clients.getFd(targetNick);
    if (targetFd == -1) {
        std::string response = "401 " + targetNick + " :No such nick\r\n";
        send(idClient, response.c_str(), response.length(), 0);
        return false;
    }

    if (!channels.isUserInChannel(channelName, targetFd)) {
        std::string response = "441 " + targetNick + " " + channelName + " :They aren't on that channel\r\n";
        send(idClient, response.c_str(), response.length(), 0);
        return false;
    }

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

    // Récupérer l'fd de la cible à partir du pseudo
    int targetId = -1;
    const std::map<int, Client*> &allClients = clients.getClients();
    for (std::map<int, Client*>::const_iterator it = allClients.begin();
         it != allClients.end(); ++it) {
        if (it->second->nickname == targetNick) {
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
