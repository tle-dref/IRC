#include "Client.hpp"
#include "Tokenisation.hpp"

bool validatePrivMsg(ClientManager clients, ChannelManager channels,
                     const TokenisedCommand &cmd, const int idClient) {
  if (cmd.getArguments().size() < 2){
	std::cerr << "error_412 : ERR_NOTEXTTOSEND" << std::endl;
	return false;
  }
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}
