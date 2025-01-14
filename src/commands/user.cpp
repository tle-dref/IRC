#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validateUser(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, int idClient) {
  if (cmd.getArguments().size() < 4) {
    std::string response = "461 USER :Not enough parameters\r\n";
    send(idClient, response.c_str(), response.length(), 0);
    return false;
  }

  if (clients.getClient(idClient)->username != "") {
    std::string response = "462 :You may not reregister\r\n";
    send(idClient, response.c_str(), response.length(), 0);
    return false;
  }

  (void)channels;
  return true;
}
