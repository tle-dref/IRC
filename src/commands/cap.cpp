#include "Server.hpp"

bool Server::validateCap(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().empty()) {
    error_461(fd, _clients.getClientname(fd), cmd.getCommand());
    return false;
  }
  return true;
}

void Server::doCap(const TokenisedCommand &cmd, int fd) {
  const std::string &subcmd = cmd.getArguments()[0];

  if (subcmd == "LS") {
    std::string response = "CAP * LS :\r\n";
    send(fd, response.c_str(), response.length(), MSG_NOSIGNAL);
  }
}
