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

  if (!_channels.isOperator(channelName, fd) && _channels.getChannel(channelName)->topicRestricted == true) {
    error_482(fd, _clients.getClientname(fd), channelName);
    return false;
  }

  return true;
}

void Server::doTopic(const TokenisedCommand &cmd, int fd) {
    const std::string &channelName = cmd.getArguments()[0];
    const std::string &topic = cmd.getArguments()[1];

    _channels.setTopic(channelName, topic);
    std::string topicMsg = ":" + _clients.getClient(fd)->nickname + " TOPIC " +
                             channelName + " :" + topic + "\r\n";
    _channels.notifyChannel(topicMsg, channelName);
}
