#include "Client.hpp"
#include "Tokenisation.hpp"

bool validatePrivmsg(ClientManager& clients, ChannelManager& channels,
                     const TokenisedCommand &cmd, const int idClient) {
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

void doPrivMsg(ClientManager& clients, ChannelManager& channels,
    const TokenisedCommand &cmd, const int idClient) {
    std::string channelName = cmd.getArguments()[0];
    std::string message = ":" + clients.getClient(idClient)->nickname + clients.getClient(idClient)->username + " PRIVMSG " + channelName + " :" + cmd.getArguments()[1];
    std::cout << "message : " << message << std::endl;
    std::cout << "channelName : " << channelName << std::endl;
    channels.notifyChannel(message, channelName);
    (void)clients;
    (void)idClient;

}
