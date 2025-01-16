#include "Server.hpp"

bool Server::validateNick(const TokenisedCommand &cmd, int fd) {
  if (!_clients.getClient(fd)->isAuthenticated) {
    error_451(fd, _clients.getClientname(fd));
    return false;
  }
  if (cmd.getArguments().size() == 0) {
    error_431(fd, _clients.getClientname(fd));
    return false;
  }

  const std::string &nickname = cmd.getArguments()[0];

  if (nickname[0] == '#' || nickname.size() > 9) {
    error_432(fd, _clients.getClientname(fd), nickname);
    return false;
  }

  if (_clients.nicknameExists(nickname)) {
    error_433(fd, _clients.getClientname(fd), nickname);
    return false;
  }
  if (nickname == _clients.getClient(fd)->nickname) {
    error_436(fd, _clients.getClientname(fd), nickname);
    return false;
  }
  return true;
}

void Server::doNick(const TokenisedCommand &cmd, int fd) {
  std::string nick = cmd.getArguments()[0];
  std::string msg =
      ":" + _clients.getClient(fd)->nickname + "!@GLMRC NICK " + nick + "\n";

  const std::map<std::string, Channel *> &channels = _channels.getChannels();
  for (std::map<std::string, Channel *>::const_iterator it = channels.begin();
       it != channels.end(); ++it) {
    const std::string &channelName = it->first;
    if (_channels.isUserInChannel(channelName, fd)) {
      _channels.notifyChannel(msg, channelName);
    }
  }

  _clients.getClient(fd)->nickname = nick;
  send(fd, msg.c_str(), msg.size(), MSG_NOSIGNAL);
}
