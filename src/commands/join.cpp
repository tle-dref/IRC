#include "Client.hpp"
#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validateJoin(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().empty()) {
    error_461(fd, _clients.getClientname(fd), cmd.getCommand());
    return false;
  }
  return true;
}

void Server::doJoin(const TokenisedCommand &cmd, int fd) {
  const std::string &channelName = cmd.getArguments()[0];

  // Vérifier si le canal existe, sinon le créer
  if (!_channels.channelExists(channelName)) {
    _channels.addChannel(channelName, new Channel(channelName));
    _channels.addOperator(channelName, _clients.getClient(fd));
  }

  // Ajouter l'utilisateur au canal
  _channels.addUser(channelName, _clients.getClient(fd));

  // Envoyer la confirmation
  std::string joinMsg = ":" + _clients.getClient(fd)->nickname +
                        "!@GLMRC JOIN " + channelName + "\r\n";
  _channels.notifyChannel(joinMsg, channelName);
}
