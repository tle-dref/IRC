#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validateMode(const TokenisedCommand &cmd, int fd) {
  std::string channelName = cmd.getArguments()[0];

  if (cmd.getArguments().size() < 2) {
    error_461(fd, _clients.getNickname(fd), channelName);
    return (false);
  }

  if (channelName == _clients.getNickname(fd)) {
    return (false);
  }

  if (channelName[0] != '#') {
    error_403(fd, _clients.getNickname(fd), channelName);
    return (false);
  } else {
    std::string flags = cmd.getArguments()[1];
    if (flags[0] == '-' || flags[0] == '+') {
      std::cout << "FLAGS LEN = " << flags.length() << std::endl;
      for (size_t i = 1; i < flags.length(); i++) {
        std::cout << "char = " << +flags[i] << std::endl;
        if (flags[i] != 'i' && flags[i] != 't' && flags[i] != 'k' &&
            flags[i] != 'o' && flags[i] != 'l') {
          std::cout << "ERROR = " << +flags[i] << std::endl;
          error_472(fd, _clients.getNickname(fd), flags[i]);
          return (false);
        }
      }
    } else {
      error_472(fd, _clients.getNickname(fd), flags[0]);
      return (false);
    }
  }
  return (true);
}

void Server::doI(std::string channelName, int sign, int fd) {
  if (sign == 0) {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setInviteOnly(channelName, false);
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " -i\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  } else {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setInviteOnly(channelName, true);
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " +i\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  }
}

void Server::doT(std::string channelName, int sign, int fd) {
  if (sign == 0) {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setTopicRestricted(channelName, false);
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " -t\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  } else {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setTopicRestricted(channelName, true);
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " +t\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  }
}

void Server::doK(std::string channelName, int sign, int fd,
                 const TokenisedCommand &cmd) {
  if (sign == 0) {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setPassword(channelName, "");
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " -k\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  } else {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setPassword(channelName, cmd.getArguments()[2]);
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " +k\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  }
}

void Server::doO(std::string channelName, int sign, int fd,
                 const TokenisedCommand &cmd) {
  if (sign == 0) {
    if (_channels.isOperator(channelName, fd)) {
      _channels.removeOperator(channelName,
                               _clients.getFd(cmd.getArguments()[2]));
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " -o\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  } else {
    if (_channels.isOperator(channelName, fd)) {
      _channels.addOperator(channelName, _clients.getClient(_clients.getFd(
                                             cmd.getArguments()[2])));
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " +o\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  }
}
void Server::doL(std::string channelName, int sign, int fd,
                 const TokenisedCommand &cmd) {
  if (sign == 0) {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setUserLimit(channelName, -1);
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " -l\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  } else {
    if (_channels.isOperator(channelName, fd)) {
      _channels.setUserLimit(channelName, atoi(cmd.getArguments()[2].c_str()));
      _channels.notifyChannel(":" + _clients.getNickname(fd) + " MODE " +
                                  channelName + " +l\r\n",
                              channelName);
    } else {
      error_482(fd, _clients.getNickname(fd), channelName);
    }
  }
}

void Server::doMode(const TokenisedCommand &cmd, int fd) {
  int sign;
  char c;

  std::string channelName = cmd.getArguments()[0];
  if (_channels.channelExists(channelName)) {
    if (_channels.isUserInChannel(channelName, fd)) {
      if (cmd.getArguments()[1][0] == '-')
        sign = 0;
      else
        sign = 1;
      for (size_t i = 1; i < cmd.getArguments()[1].length(); ++i) {
        c = cmd.getArguments()[1][i];
        if (c == 'i')
          doI(channelName, sign, fd);
        else if (c == 't')
          doT(channelName, sign, fd);
        else if (c == 'k')
          doK(channelName, sign, fd, cmd);
        else if (c == 'o')
          doO(channelName, sign, fd, cmd);
        else if (c == 'l')
          doL(channelName, sign, fd, cmd);
      }
    }
  } else {
    error_403(fd, _clients.getClientname(fd), channelName);
  }
}