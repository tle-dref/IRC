#include "Client.hpp"
#include "Tokenisation.hpp"

bool validateNick(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient) {
  if (cmd.getArguments().empty()) {
    std::cerr << "error_431 : ERR_NOORIGIN" << std::endl;
    return false;
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (nickname.length() > 9 || !isalpha(nickname[0])) {
    std::cerr << "error_432 : ERR_ERRONEUSNICKNAME" << std::endl;
    return false;
  }
  if (clients.usernameExists(nickname)) {
    std::cerr << "error_433 : ERR_NICKNAMEINUSE" << std::endl;
    return false;
  }
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}