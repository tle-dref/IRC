#include "Server.hpp"

bool Server::validateNick(const TokenisedCommand &cmd, int fd) {
  if (!_clients.getClient(fd)->isAuthenticated) {
    std::string errorMsg =
        "ERROR :Vous devez d'abord vous authentifier avec PASS\n";
    send(fd, errorMsg.c_str(), errorMsg.size(), 0);
    return false;
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (_clients.nicknameExists(nickname)) {
    std::string response = "433 " + nickname + " :Nickname is already in use\n";
    send(fd, response.c_str(), response.length(), 0);
    return false;
  }
  return cmd.getArguments().size() > 0;
}

void Server::doNick(const TokenisedCommand &cmd, int fd) {
  std::string nick = cmd.getArguments()[0];
  _clients.getClient(fd)->nickname = nick;
  std::cout << "Client a défini son pseudonyme : " << nick << std::endl;
}