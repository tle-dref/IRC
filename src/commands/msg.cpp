#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validatePrivmsg(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().size() < 2) {
    error_461(fd, _clients.getClientname(fd), cmd.getCommand());
    return false;
  }
  return true;
}

void Server::doPrivmsg(const TokenisedCommand &cmd, int fd) {
  std::string channelName = cmd.getArguments()[0];

  std::cout << "channelName : " << channelName << " | fd : " << fd
            << " | msg : " << cmd.getArguments()[1] << "" << std::endl;

  if (channelName == "bot") {
    botResponse(cmd.getArguments()[1], fd);
    return;
  }

  std::string::iterator it = channelName.begin();
  for (; it != channelName.end(); it++) {
    if (*it == '#') {
      break;
    }
  }
  if (it == channelName.end()) {
    std::string clientName = channelName;
    std::string message = ":" + _clients.getClient(fd)->nickname + " PRIVMSG " +
                          clientName + " :" + cmd.getArguments()[1] + "\n";
    _clients.msgClient(message, clientName, fd);
    return;
  }
  // cmd.print();
  std::string message = ":" + _clients.getClient(fd)->nickname + " PRIVMSG " +
                        channelName + " :" + cmd.getArguments()[1] + "\n";
  // std::string msg = ":" + clients.getClient(fdClient)->nickname + " " +
  // cmd.getArguments()[1];
  //  std::cout << "message : " << msg << std::endl;
  // std::cout << "channelName : " << channelName << std::endl;
  _channels.msgChannel(message, channelName, fd);
}
