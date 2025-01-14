#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validatePart(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, int idClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}

void Server::doPart(ClientManager& clients, ChannelManager& channels,
            const TokenisedCommand &cmd, int fdClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)fdClient;
  // TODO: implement doPart function
}