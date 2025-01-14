#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validateTopic(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, int idClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}

void Server::doTopic(ClientManager& clients, ChannelManager& channels,
            const TokenisedCommand &cmd, int fdClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)fdClient;
  // TODO: implement doTopic
}