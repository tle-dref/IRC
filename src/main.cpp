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

  std::string n = "#myChannel";

  ClientManager clients;
  Channel myChannel(n);
  ChannelManager channels;
  Client client1;
  Client client2;
  client1.nickname = "myNickname";
  client1.username = "myUsername";
  client1.hostname = "myHostname";

  clients.addClient(client1);
  clients.addClient(client2);
  channels.addChannel(n, myChannel);
  channels.banUser(n, client1.id);
  channels.unbanUser(n, client1.id);
  channels.getBannedUser(n);
  channels.setUserLimit(n, 2);
  channels.addUser(n, &client1);
  channels.addUser(n, &client2);

  channels.setPassword(n,"ptdr");
  dispatchCommand(clients, channels, cmd, client1.id);
  dispatchCommand(clients, channels, cmd, client2.id);
  //   cmd.print();
  clients.printClients();

  return 0;
}
