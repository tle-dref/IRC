#include "Client.hpp"
#include "Tokenisation.hpp"

bool validateMode(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}