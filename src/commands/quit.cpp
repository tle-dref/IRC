#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validateQuit(const TokenisedCommand &cmd, int fd) {
  (void)cmd;
  (void)fd;
  return true;
}

void Server::doQuit(const TokenisedCommand &cmd, int fd) {
  std::string quitMsg;
  if (!cmd.getArguments().empty()) {
    quitMsg = cmd.getArguments()[0];
  }
  else {
      quitMsg = "Leaving";
  }


  const std::map<std::string, Channel *> &inChannel = _channels.getChannels();
  for (std::map<std::string, Channel *>::const_iterator it = inChannel.begin();
       it != inChannel.end(); ++it) {
    std::cout << "fd = " << fd << "    et channel name = " << it->first
              << std::endl;
    if (it->second && _channels.isUserInChannel(it->first, fd)) {
      quitMsg = ":" + _clients.getClient(fd)->nickname + "!" +
                _clients.getClientname(fd) + "!@GLMRC QUIT " + ":" +
                cmd.getArguments()[0] + "\r\n";
      _channels.notifyChannel(quitMsg, it->first);
    }
  }
  for (std::map<std::string, Channel *>::const_iterator it = inChannel.begin();
       it != inChannel.end(); ++it) {
    _channels.removeUser(it->first, fd);
  }
   std::string msg = ":" + _clients.getClient(fd)->nickname + "!@GLMRC QUIT " + quitMsg + "\r\n";
   _clients.removeClient(fd);
}
