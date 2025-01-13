#include "Client.hpp"
#include "Tokenisation.hpp"

void validateNick(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty()) {
    throw std::runtime_error("error_431");
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (nickname.length() > 9 || !isalpha(nickname[0])) {
    throw std::runtime_error("error_432");
  }
  if (clients.usernameExists(nickname)) {
    throw std::runtime_error("error_433");
  }
}