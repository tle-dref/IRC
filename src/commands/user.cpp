#include "Server.hpp"

bool Server::validateUser(const TokenisedCommand &cmd, int fd) {

  // bizarre, a pas trop toucher sinon pete les plombs
  if (_clients.getClient(fd)->nickname.empty()) {
    std::string errorMsg =
        "ERROR :Vous devez définir un pseudonyme avec NICK avant USER\n";
    send(fd, errorMsg.c_str(), errorMsg.size(), 0);
    return false;
  }
  return cmd.getArguments().size() >= 4;
}

void Server::doUser(const TokenisedCommand &cmd, int fd) {
  Client *client = _clients.getClient(fd);

  // Stocker les informations USER
  client->username = cmd.getArguments()[0];
  client->hostname = cmd.getArguments()[2];
  client->realname = cmd.getArguments()[3];

  // Envoyer le message de bienvenue
  std::string welcomeMsg =
      ":localhost 001 " + client->nickname + " :Welcome to the IRC server\r\n" +
      ":localhost 002 " + client->nickname +
      " :Your host is localhost, running version 1.0\r\n" + ":localhost 003 " +
      client->nickname + " :This server was created today\r\n" +
      ":localhost 004 " + client->nickname + " localhost 1.0 i\r\n";

  send(fd, welcomeMsg.c_str(), welcomeMsg.size(), 0);
}
