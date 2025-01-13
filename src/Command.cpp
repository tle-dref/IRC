#include "Command.hpp"
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

void dispatchCommand(ClientManager clients, const TokenisedCommand &cmd) {
  int commandIndex = CommandList::findCommandIndex(cmd.getCommand());

  switch (commandIndex) {
  case 0: // NICK
    validateNick(clients, cmd);
    // doNick();
    break;

  case 1: // USER
    validateUser(clients, cmd);
    // doUser();
    break;

  case 2: // JOIN
    validateJoin(clients, cmd);
    // doJoin();
    break;

  case 3: // PRIVMSG
    validatePrivMsg(clients, cmd);
    // doPrivMsg();
    break;

  case 4: // QUIT
    validateQuit(clients, cmd);
    // doQuit();
    break;

  case 5: // PONG
    validatePong(clients, cmd);
    // doPong();
    break;

  case 6: // KICK
    validateKick(clients, cmd);
    // doKick();
    break;

  case 7: // MODE
    validateMode(clients, cmd);
    // doMode();
    break;

  case 8: // PASS
    validatePass(clients, cmd);
    // doPass();
    break;

  case 9: // TOPIC
    validateTopic(clients, cmd);
    // doTopic();
    break;

  default:
    handleInvalidCommand(clients, cmd.getCommand());
    break;
  }
}

void handleInvalidCommand(ClientManager clients, const std::string &cmd) {
  throw std::runtime_error("error_421");
  (void)clients;
  (void)cmd;
}
