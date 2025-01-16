#include "Channel.hpp" // Pour Channel, ChannelManager
#include "Client.hpp"  // Pour Client, ClientManager
#include "Server.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
    return (1);
  }
  int port = std::atoi(argv[1]);
  std::string password = argv[2];
  ClientManager clients;
  ChannelManager channels;

  Server server(port, password);
  server.createBot();
  server.run();
  return (0);
}
