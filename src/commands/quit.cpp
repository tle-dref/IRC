#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validateQuit(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, int idClient)
{
  // Assurer que la commande a des arguments valides (par exemple un message de déconnexion optionnel)
  if (cmd.getArguments().size() > 1)
  {
    std::cerr << "error_461 : ERR_NEEDMOREPARAMS" << std::endl;
    return (false);
  }
  // Si le client n'est pas connecté, il ne peut pas quitter
  if (clients.getClient(idClient) == NULL)
  {
    std::cerr << "error_442 : ERR_NOTONCHANNEL" << std::endl;
    return (false);
  }
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return (true);
}

void Server::doQuit(ClientManager& clients, ChannelManager& channels,
            const TokenisedCommand &cmd, int idClient)
{
  Client  *client;

  client = clients.getClient(idClient);
  // Message de déconnexion, s'il y en a un
  std::string quitMessage = cmd.getArguments().empty() ? "Quit" : cmd.getArguments()[0];
  std::cout << "Client " << client->nickname << " is quitting: " << quitMessage << std::endl;
  // Quitter tous les canaux
/*  std::set<std::string> channelsList = channels.getJoinedChannels(idClient);
  for (const std::string &channelName : channelsList)
  {
    channels.removeUser(channelName, idClient);
    std::cout << "Client " << client->nickname << " left channel " << channelName << std::endl;
  }
  close(client->getFd());
  clients.removeClient(idClient);
  // Autres actions de nettoyage ou déconnexion si nécessaires...*/
  (void)channels;
}
