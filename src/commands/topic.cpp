#include "Client.hpp"
#include "Tokenisation.hpp"

bool validateTopic(ClientManager& clients, ChannelManager& channels,
                   const TokenisedCommand &cmd, const int idClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}