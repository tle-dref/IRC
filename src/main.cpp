#include "ClientManager.hpp"
#include "Tokenisation.hpp"
#include "commandHandler.hpp"
#include <iostream>

int main(int ac, char **av) {
  if (ac != 2) {
    std::cerr << "./ircserv <command>" << std::endl;
  }
  std::string rawCommand = av[1];

  try {
    TokenisedCommand cmd = tokenize(rawCommand);
    if (!cmd.isValid()) {
      std::cerr << "Invalid command received." << std::endl;
      return 1;
    }
    ClientManager client;
    dispatchCommand(client, cmd);
    cmd.print();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
