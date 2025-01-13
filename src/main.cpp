#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Tokenisation.hpp"
#include <iostream>

int main(int ac, char **av) {
  if (ac != 2) {
    std::cerr << "./ircserv <command>" << std::endl;
    return 1;
  }
  std::string rawCommand = av[1];

  TokenisedCommand cmd = tokenize(rawCommand);
  if (!cmd.isValid()) {
    std::cerr << "Invalid command received." << std::endl;
    return 1;
  }
  
  ClientManager clients;
  ChannelManager channels;
  Client client1;
  Client client2;
  clients.addClient(client1);
  clients.addClient(client2);
  dispatchCommand(clients, channels, cmd, client1.id);
  cmd.print();
  clients.printClients();

  return 0;
}
