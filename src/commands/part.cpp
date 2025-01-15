#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validatePart(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().size() < 1) {
    error_461(fd, _clients.getClientname(fd), cmd.getCommand());
    return false;
  }

  std::string channelName = cmd.getArguments()[0];
  if (_channels.getChannel(channelName) == NULL) {
    error_403(fd, _clients.getClientname(fd), channelName);
    return false;
  }

  if (!_channels.isUserInChannel(channelName, fd)) {
    error_442(fd, _clients.getClientname(fd), channelName);
    return false;
  }

  return true;
}

void Server::doPart(const TokenisedCommand &cmd, int fd) {
  std::string channelName = cmd.getArguments()[0];

  std::string partMsg =
      ":" + _clients.getClient(fd)->nickname + " PART " + channelName + "\r\n";
  _channels.notifyChannel(partMsg, channelName);
  _channels.removeUser(channelName, fd);
}