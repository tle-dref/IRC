#include "Client.hpp"
#include "Tokenisation.hpp"

void validateUser(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 4)
    throw std::runtime_error("error_461"); // ERR_NEEDMOREPARAMS

  // if (clients.isRegister())
  //   throw std::runtime_error("error_462"); // ERR_ALREADYREGISTERED

  (void)clients;
}
