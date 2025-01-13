#include "Client.hpp"
#include "Tokenisation.hpp"

bool validatePass(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}