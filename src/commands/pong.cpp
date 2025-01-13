#include "Client.hpp"
#include "Tokenisation.hpp"

void validatePong(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_409");
  (void)clients;
}