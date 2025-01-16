#include "Client.hpp"
#include "Server.hpp"
#include "Tokenisation.hpp"

std::vector<std::string> splitString(const std::string &str, char delim) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string item;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}

bool Server::validateJoin(const TokenisedCommand &cmd, int fd) {
  if (cmd.getArguments().empty()) {
    error_461(fd, _clients.getClientname(fd), cmd.getCommand());
    return false;
  }
  return true;
}

void Server::doJoin(const TokenisedCommand &cmd, int fd) {
  const std::string &channelName = cmd.getArguments()[0];

  std::vector<std::string> channelNames = splitString(channelName, ',');

  // Vérifier si le canal existe, sinon le créer
  for (std::vector<std::string>::iterator it = channelNames.begin();
       it != channelNames.end(); it++) {
    std::string channelName = *it;
    if (!_channels.channelExists(channelName)) {
      _channels.addChannel(channelName, new Channel(channelName));
      _channels.addOperator(channelName, _clients.getClient(fd));
    }
    // Ajouter l'utilisateur au canal
    if (_channels.getChannel(channelName)->inviteOnly) {
      if (_channels.isUserInvited(channelName, fd))
        if (_channels.getChannel(channelName)->password.empty())
          _channels.addUser(channelName, _clients.getClient(fd));
        else {
          if (cmd.getArguments()[1] ==
              _channels.getChannel(channelName)->password)
            _channels.addUser(channelName, _clients.getClient(fd));
          else {
            error_475(fd, _clients.getClientname(fd), channelName);
            return;
          }
        }
      else {
        error_473(fd, _clients.getClientname(fd), channelName);
        return;
      }
    }
    if (_channels.getChannel(channelName)->password.empty())
      _channels.addUser(channelName, _clients.getClient(fd));
    else {
      if (cmd.getArguments()[1] == _channels.getChannel(channelName)->password)
        _channels.addUser(channelName, _clients.getClient(fd));
      else {
        error_475(fd, _clients.getClientname(fd), channelName);
        return;
      }
    }
    // Envoyer la confirmation
    std::string joinMsg = ":" + _clients.getClient(fd)->nickname +
                          "!@GLMRC JOIN " + channelName + "\r\n";
    _channels.notifyChannel(joinMsg, channelName);
  }
}
