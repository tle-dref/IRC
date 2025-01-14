#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validatePing(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, int idClient) {
  if (cmd.getArguments().empty()) {
    std::cerr << "error_461 : ERR_NEEDMOREPARAMS" << std::endl;
    return false;
  }
  (void)clients;
  (void)channels;
  (void)idClient;
  return true;
}

void Server::doPing(ClientManager& clients, ChannelManager& channels,
            const TokenisedCommand &cmd, int fdClient) {
  std::string response = "PONG :" + cmd.getArguments()[0] + "\r\n";
  send(fdClient, response.c_str(), response.length(), 0);
  
  (void)clients;
  (void)channels;
}
