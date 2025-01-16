#include "Server.hpp"

bool Server::validateNick(const TokenisedCommand &cmd, int fd) {
  if (!_clients.getClient(fd)->isAuthenticated) {
    error_451(fd, _clients.getClientname(fd));
    std::cout << "caca\n";
    return false;
  }
  if (cmd.getArguments().size() == 0) {
    error_431(fd, _clients.getClientname(fd));
    std::cout << "cacat\n";
    return false;
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (nickname.size() > 9) {
    error_432(fd, _clients.getClientname(fd), nickname);
    std::cout << "cacatt\n";
    return false;
  }
  if (_clients.nicknameExists(nickname)) {
    error_433(fd, _clients.getClientname(fd), nickname);
    std::cout << "cacajijj\n";
    return false;
  }
  if (nickname == _clients.getClient(fd)->nickname) {
    error_436(fd, _clients.getClientname(fd), nickname);
    std::cout << "cacawqwewq\n";
    return false;
  }
  return true;
}

void Server::doNick(const TokenisedCommand &cmd, int fd) {
  std::string nick = cmd.getArguments()[0];
    std::string msg = ":" + _clients.getClient(fd)->nickname + "!@GLMRC NICK " + nick + "\n";
  _clients.getClient(fd)->nickname = nick;
    send(fd, msg.c_str(), msg.size(), 0);
}
