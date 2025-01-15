#include "Client.hpp"
#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validatePass(const TokenisedCommand &cmd, int fd) {
  if (!cmd.getArguments().size()) {
    std::string errorMsg = "ERROR :Mot de passe requis\r\n";
    send(fd, errorMsg.c_str(), errorMsg.size(), 0);
    return false;
  }
  return true;
}

void Server::doPass(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments()[0] == this->password) {
    _clients.getClient(fd)->isAuthenticated = true;
    std::cout << "Mot de passe correct pour le client (fd: " << fd << ")"
              << std::endl;
  } else {
    std::string errorMsg = "ERROR :Mot de passe incorrect\r\n";
    send(fd, errorMsg.c_str(), errorMsg.size(), 0);
    close(fd);
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
    // delete _clients[fd];
    _clients.removeClient(fd);
  }
}
