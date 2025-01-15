#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validateKick(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().size() < 2) {
    std::string response = "461 KICK :Not enough parameters\n";
    std::cout << response << std::endl;
    return false;
  }

  const std::string &channel = cmd.getArguments()[0];
  const std::string &target = cmd.getArguments()[1];

  // Vérifier si le canal existe
  if (!_channels.channelExists(channel)) {
    std::string response = "403 " + channel + " :No such channel\n";
    std::cout << response << std::endl;
    return false;
  }

  // Vérifier si l'utilisateur est opérateur du canal
  if (!_channels.isOperator(channel, fd)) {
    std::string response = "482 " + channel + " :You're not channel operator\n";
    std::cout << response << std::endl;
    return false;
  }

  // Vérifier si la cible existe dans le canal
  int targetFd = _clients.getFd(target);
  if (targetFd == -1 || !_channels.isUserInChannel(channel, targetFd)) {
    std::string response =
        "441 " + target + " " + channel + " :They aren't on that channel\n";
    std::cout << response << std::endl;
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
