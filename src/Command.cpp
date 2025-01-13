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
    commands.push_back("PONG");
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

void dispatchCommand(ClientManager clients, ChannelManager channels,
                     const TokenisedCommand &cmd, const int idClient) {
  int commandIndex = CommandList::findCommandIndex(cmd.getCommand());

  switch (commandIndex) {
  case 0: // NICK
    validateNick(clients, channels, cmd, idClient);
    // doNick();
    break;

  case 1: // USER
    if (validateUser(clients, channels, cmd, idClient)) {
      // doUser();
    };
    break;

  case 2: // JOIN
    if (validateJoin(clients, channels, cmd, idClient)) {
      // doJoin();
    }
    break;

  case 3: // PRIVMSG
    if (validatePrivMsg(clients, channels, cmd, idClient)) {
      // doPrivMsg();
    }
    break;

  case 4: // QUIT
    if (validateQuit(clients, channels, cmd, idClient)) {
      // doQuit();
    }
    break;

  case 5: // PONG
    if (validatePong(clients, channels, cmd, idClient)) {
      // doPong();
    }
    break;

  case 6: // KICK
    if (validateKick(clients, channels, cmd, idClient)) {
      // doKick();
    }
    break;

  case 7: // MODE
    if (validateMode(clients, channels, cmd, idClient)) {
      // doMode();
    }
    break;

  case 8: // PASS
    if (validatePass(clients, channels, cmd, idClient)) {
      // doPass();
    }
    break;

  case 9: // TOPIC
    if (validateTopic(clients, channels, cmd, idClient)) {
      // doTopic();
    }
    break;

  case 10: // PART
    if (validatePart(clients, channels, cmd, idClient)) {
      // doPart();
    }
    break;

  default:
    handleInvalidCommand(clients, cmd.getCommand(), idClient);
    break;
  }
}

void handleInvalidCommand(ClientManager clients, const std::string &cmd, const int idClient) {
  std::cerr << "error_421: ERR_UNKNOWNCOMMAND" << std::endl;
  (void)clients;
  (void)cmd;
  (void)idClient;
}
