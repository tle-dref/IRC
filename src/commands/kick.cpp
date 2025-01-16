#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validateKick(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().size() < 2) {
    error_461(fd, _clients.getNickname(fd), cmd.getCommand());
    return false;
  }

  const std::string &channel = cmd.getArguments()[0];
  const std::string &target = cmd.getArguments()[1];

  // Vérifier si le canal existe
  if (!_channels.channelExists(channel)) {
    error_403(fd, _clients.getNickname(fd), channel);
    return false;
  }

  // Vérifier si l'utilisateur est opérateur du canal
  if (!_channels.isOperator(channel, fd)) {
    error_482(fd, _clients.getNickname(fd), channel);
    return false;
  }

  // Vérifier si la cible existe dans le canal
  int targetFd = _clients.getFd(target);
  if (targetFd == -1 || !_channels.isUserInChannel(channel, targetFd)) {
    error_441(fd, _clients.getNickname(fd), channel);
    std::string errorMsg = ":" + _clients.getNickname(fd) + "!" +
                           _clients.getClientname(fd) + "@I.R.SIUSIU NOTICE " +
                           channel + " :User " + target + " does not exist\n";
    send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
    return false;
  }

  return true;
}

void Server::doKick(const TokenisedCommand &cmd, int fd) {
  int targetFd = _clients.getFd(cmd.getArguments()[1]);
  std::string channelName = cmd.getArguments()[0];

  std::string kickMsg = ":" + _clients.getClient(fd)->nickname + " KICK " +
                        channelName + " " + cmd.getArguments()[1] + "\r\n";
  std::string toKick = "PART " + channelName + "\r\n";
  TokenisedCommand cmdToKick = tokenize(toKick);
  doPart(cmdToKick, targetFd);
}
