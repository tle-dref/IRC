#include "Client.hpp"
#include "Tokenisation.hpp"

bool validateNick(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, const int idClient) {
  if (cmd.getArguments().empty()) {
    std::string response = "431 :No nickname given\r\n";
    send(idClient, response.c_str(), response.length(), 0);
    return false;
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (nickname.length() > 9 || !isalpha(nickname[0])) {
    std::string response = "432 " + nickname + " :Erroneous nickname\r\n";
    send(idClient, response.c_str(), response.length(), 0);
    return false;
  }
  if (clients.nicknameExists(nickname)) {
    std::string response = "433 " + nickname + " :Nickname is already in use\r\n";
    send(idClient, response.c_str(), response.length(), 0);
    return false;
  }
  (void)channels;
  return true;
}