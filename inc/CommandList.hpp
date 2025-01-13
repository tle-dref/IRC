#pragma once
#include <string>
#include <vector>

class CommandList {
public:
  static const std::vector<std::string> &getCommands();
  static int findCommandIndex(const std::string &command);
};
