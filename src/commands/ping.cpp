#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validatePing(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().empty()) {
    error_409(fd, _clients.getClientname(fd));
    return false;
  }
  return true;
}

void Server::doPong(const TokenisedCommand &cmd, int fd) {
  std::string token = cmd.getArguments()[0];
  std::string response = "PONG :" + token + "\r\n";
  send(fd, response.c_str(), response.size(), 0);
  std::cout << "Send PONG response: " << response;
}
