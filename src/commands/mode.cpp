#include "Server.hpp"
#include "Tokenisation.hpp"

bool Server::validateMode(const TokenisedCommand &cmd, int fd) {
  std::string channelName = cmd.getArguments()[0];

  if (cmd.getArguments().size() != 2) {
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

void Server::doMode(const TokenisedCommand &cmd, int fd) {
  (void)cmd;
  (void)fd;
}