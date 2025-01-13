#include "CommandList.hpp"

const std::vector<std::string>& CommandList::getCommands() {
    static std::vector<std::string> commands;
    if (commands.empty()) {
        commands.push_back("NICK");
        commands.push_back("USER");
        commands.push_back("JOIN");
        commands.push_back("PRIVMSG");
        commands.push_back("QUIT");
        commands.push_back("PING");
        commands.push_back("PONG");
    }
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
