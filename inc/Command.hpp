#pragma once
#include "Client.hpp"
#include "Tokenisation.hpp"
#include <string>
#include <vector>

class CommandList {
public:
  static const std::vector<std::string> &getCommands();
  static int findCommandIndex(const std::string &cmd);
};

class CommandHandler {
public:

  // Commandes d'authentification

};
