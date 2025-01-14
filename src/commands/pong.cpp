#include "Client.hpp"
#include "Tokenisation.hpp"

bool validatePing(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, const int idClient) {
  if (cmd.getArguments().empty()){
	std::cerr << "error_409 : ERR_NOORIGIN" << std::endl;
    return false;
  }
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}