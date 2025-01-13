#include "Client.hpp"
#include "Tokenisation.hpp"

void validatePrivMsg(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 2)
    throw std::runtime_error("error_412");
  (void)clients;
}

