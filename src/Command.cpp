#include "Command.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>

const std::vector<std::string> &CommandList::getCommands() {
  static std::vector<std::string> commands;
  if (commands.empty()) {
    commands.push_back("NICK");
    commands.push_back("USER");
    commands.push_back("JOIN");
    commands.push_back("PRIVMSG");
    commands.push_back("QUIT");
    commands.push_back("PING");
    commands.push_back("KICK");
    commands.push_back("MODE");
    commands.push_back("PASS");
    commands.push_back("TOPIC");
    commands.push_back("PART");
  }
  return commands;
}

int CommandList::findCommandIndex(const std::string &cmd) {
  const std::vector<std::string> &cmds = getCommands();
  for (size_t i = 0; i < cmds.size(); ++i) {
    if (cmds[i] == cmd) {
      return i;
    }
  }
  return -1;
}

void dispatchCommand(ClientManager& clients, ChannelManager& channels,
                     const TokenisedCommand &cmd, const int fd) {
  int commandIndex = CommandList::findCommandIndex(cmd.getCommand());

  // Handle CAP command separately as it's not in our main command list
  if (cmd.getCommand() == "CAP") {
    // Just acknowledge CAP LS for now
    if (cmd.getArguments().size() > 0 && cmd.getArguments()[0] == "LS") {
      std::string response = "CAP * LS :\r\n";
      send(fd, response.c_str(), response.length(), 0);
    }
    return;
  }

  switch (commandIndex) {
  case 0: // NICK
    if (validateNick(clients, channels, cmd, fd)) {
      clients.setNickname(fd, cmd.getArguments()[0]);
    }
    break;

  case 1: // USER
    if (validateUser(clients, channels, cmd, fd)) {
      clients.setClientname(fd, cmd.getArguments()[0]);
      clients.setHostname(fd, cmd.getArguments()[2]);
    }
    break;

  case 2: // JOIN
    if (validateJoin(clients, channels, cmd, fd)) {
      doJoin(clients, channels, cmd, fd);
    }
    break;

  case 3: // PRIVMSG
    if (validatePrivmsg(clients, channels, cmd, fd)) {
      doPrivMsg(clients, channels, cmd, fd);
    }
    break;

  case 4: // QUIT
    if (validateQuit(clients, channels, cmd, fd)) {
      // doQuit();
    }
    break;

  case 5: // PING
    if (validatePing(clients, channels, cmd, fd)) {
      std::string response = "PONG :" + cmd.getArguments()[0] + "\r\n";
      send(fd, response.c_str(), response.length(), 0);
    }
    break;

  case 6: // KICK
    if (validateKick(clients, channels, cmd, fd)) {
      // doKick();
    }
    break;

  case 7: // MODE
    if (validateMode(clients, channels, cmd, fd)) {
      // doMode();
    }
    break;

  case 8: // PASS
    if (validatePass(clients, channels, cmd, fd)) {
      clients.setAuthenticated(fd, true);
    }
    break;

  case 9: // TOPIC
    if (validateTopic(clients, channels, cmd, fd)) {
      // doTopic();
    }
    break;

  case 10: // PART
    if (validatePart(clients, channels, cmd, fd)) {
      // doPart();
    }
    break;

  default:
    handleInvalidCommand(clients, cmd.getCommand(), fd);
    break;
  }
}

void handleInvalidCommand(ClientManager& clients, const std::string &cmd,
                          const int fd) {
  std::string response = "421 " + clients.getNickname(fd) + " " + cmd + " :Unknown command\r\n";
  send(fd, response.c_str(), response.length(), 0);
}
