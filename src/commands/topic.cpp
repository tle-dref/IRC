#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validateTopic(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().size() < 2) {
    error_461(fd, _clients.getClientname(fd), cmd.getCommand());
    return false;
  }

  const std::string &channelName = cmd.getArguments()[0];
  if (!_channels.channelExists(channelName)) {
    error_403(fd, _clients.getClientname(fd), channelName);
    return false;
  }

  if (!_channels.isUserInChannel(channelName, fd)) {
    error_442(fd, _clients.getClientname(fd), channelName);
    return false;
  }

  if (!_channels.isOperator(channelName, fd)) {
    error_482(fd, _clients.getClientname(fd), channelName);
    return false;
  }

  return true;
}

void Server::doTopic(const TokenisedCommand &cmd, int fd) {
  (void)cmd;
  (void)fd;
}