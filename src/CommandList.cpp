#include "CommandList.hpp"

const std::vector<std::string> &CommandList::getCommands() {
  static const std::vector<std::string> commands = {
      "NICK", "USER", "JOIN", "PRIVMSG", "QUIT", "PING", "PONG"};
  return commands;
}

int CommandList::findCommandIndex(const std::string &command) {
  const std::vector<std::string> &commands = getCommands();
  for (size_t i = 0; i < commands.size(); ++i) {
    if (commands[i] == command) {
      return i;
    }
  }
  return -1;
}
