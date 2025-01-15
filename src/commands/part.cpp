#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validatePart(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().size() < 1) {
    std::cerr << "error_461" << std::endl;
    return false;
  }

  std::string channelName = cmd.getArguments()[0];
  if (_channels.getChannel(channelName) == NULL) {
    std::cerr << "error_403 " << channelName << std::endl;
    return false;
  }

  if (!_channels.isUserInChannel(channelName, fd)) {
    std::cerr << "error_442 " << channelName << std::endl;
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