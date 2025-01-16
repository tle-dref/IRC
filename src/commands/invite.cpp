#include "Server.hpp"

bool Server::validateInvite(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().size() < 2) {
    error_461(fd, _clients.getNickname(fd), cmd.getCommand());
    return false;
  }

  const std::string &channel = cmd.getArguments()[1];
  const std::string &target = cmd.getArguments()[0];

  if (!_channels.channelExists(channel)) {
    error_403(fd, _clients.getNickname(fd), channel);
    return false;
  }

  if (!_channels.isUserInChannel(channel, fd)) {
    error_442(fd, _clients.getNickname(fd), channel);
    return false;
  }

  int target_fd = _clients.getFd(target);
  if (target_fd == -1 || _channels.isUserInChannel(channel, target_fd)) {
    error_443(fd, _clients.getNickname(fd), channel);
    return false;
  }

  return true;
}
void Server::doInvite(const TokenisedCommand &cmd, int fd) {
  const std::string &targetName = cmd.getArguments()[0];
  const std::string &channelName = cmd.getArguments()[1];
  int targetFd = _clients.getFd(targetName);

  std::string inviteMsg = ":" + _clients.getNickname(fd) + " INVITE " +
                          targetName + " " + channelName + "\r\n";
  send(targetFd, inviteMsg.c_str(), inviteMsg.length(), 0);

  _channels.inviteUser(channelName, _clients.getClient(targetFd));
}