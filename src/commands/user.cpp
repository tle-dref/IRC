#include "Client.hpp"
#include "Tokenisation.hpp"

bool validateUser(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient) {
  if (cmd.getArguments().size() < 4){
	std::cerr << "error_461 : ERR_NEEDMOREPARAMS" << std::endl;
    return false;
  }

  // if (clients.isRegister())
  //   throw std::runtime_error("error_462"); // ERR_ALREADYREGISTERED

  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}
