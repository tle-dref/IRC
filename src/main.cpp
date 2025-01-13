#include "Client.hpp"
#include "Tokenisation.hpp"
#include "Command.hpp"
#include <iostream>

int main(int ac, char **av) {
  if (ac != 2) {
    std::cerr << "./ircserv <command>" << std::endl;
	return 1;
  }
  std::string rawCommand = av[1];

  try {
    TokenisedCommand cmd = tokenize(rawCommand);
    if (!cmd.isValid()) {
      std::cerr << "Invalid command received." << std::endl;
      return 1;
    }
    ClientManager clients;
	Client client1;
	Client client2;
	clients.addClient(client1);
	clients.addClient(client2);
    dispatchCommand(clients, cmd);
    cmd.print();
	clients.printClients();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
