#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validatePrivmsg(ClientManager& clients, ChannelManager& channels,
                     const TokenisedCommand &cmd, int idClient) {
  if (cmd.getArguments().size() < 2){
	std::cerr << "error_412 : ERR_NOTEXTTOSEND" << std::endl;
	return false;
  }
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}

void Server::doPrivMsg(ClientManager& clients, ChannelManager& channels,
    const TokenisedCommand &cmd, int fdClient) {
    std::string channelName = cmd.getArguments()[0];
    std::string message = ":" + clients.getClient(fdClient)->nickname + clients.getClient(fdClient)->username + " PRIVMSG " + channelName + " :" + cmd.getArguments()[1];
    std::cout << "message : " << message << std::endl;
    std::cout << "channelName : " << channelName << std::endl;
    channels.notifyChannel(message, channelName);
    (void)clients;
    (void)fdClient;

}
