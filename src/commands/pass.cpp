#include "Client.hpp"
#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validatePass(const TokenisedCommand &cmd, int fd) {
  if (!cmd.getArguments().size()) {
    error_461(fd, _clients.getClientname(fd), cmd.getCommand());
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
    std::string errorMsg = "ERROR :Mot de passe incorrect\n";
    send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
    close(fd);
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
    // delete _clients[fd];
    _clients.removeClient(fd);
  }
}
