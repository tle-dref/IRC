#include "validation.hpp"
#include <iostream>
#include <stdexcept>

void validateNick(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty()) {
    throw std::runtime_error("error_431");
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (nickname.length() > 9 || !isalpha(nickname[0])) {
    throw std::runtime_error("error_432");
  }
  (void)client;
}

void validateUser(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 4)
    throw std::runtime_error("error_461");
  (void)client;
}

void validateJoin(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_461");
  (void)client;
}

void validatePrivMsg(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 2)
    throw std::runtime_error("error_412");
  (void)client;
}

void validateQuit(ClientManager client, const TokenisedCommand &cmd) {
  (void)client;
  (void)cmd;
}

void validatePing(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_409");
  (void)client;
}

void validatePong(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_409");
  (void)client;
}