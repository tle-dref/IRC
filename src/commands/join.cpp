#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool validateJoin(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, int idClient) {
  if (cmd.getArguments().empty()) {
    std::cerr << "error_461 : ERR_NEEDMOREPARAMS" << std::endl;
    return false;
  }

  std::string channelName = cmd.getArguments()[0];

  if (channelName.empty() || channelName[0] != '#' ||
      channelName.length() > 50) {
    std::cerr << "error_476 : ERR_BADCHANMASK" << std::endl;
    return false;
  }

  if (channels.isBanned(channelName, idClient)) {
    std::cerr << "error_474 : ERR_BANNEDFROMCHAN" << std::endl;
    return false;
  }

  if (channels.isFull(channelName)) {
    std::cerr << "error_471 : ERR_CHANNELISFULL" << std::endl;
    return false;
  }

  //   if (channels.isInviteOnly(channelName)) {
  //     throw std::runtime_error("error_473"); // ERR_INVITEONLYCHAN
  //   }

  if (channels.isPasswordProtected(channelName) &&
      channels.getPassword(channelName) != cmd.getArguments()[1]) {
    std::cerr << "error_475 : ERR_BADCHANNELKEY" << std::endl;
    return false;
  }

  //   if (clients.getJoinedChannelsCount() >= server.getMaxChannelsPerUser()) {
  //     throw std::runtime_error("error_405"); // ERR_TOOMANYCHANNELS
  //   }

  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}

void doJoin(ClientManager clients, ChannelManager channels,
            const TokenisedCommand &cmd, int idClient) {

  std::string channelName = cmd.getArguments()[0];
  if (channels.getChannel(channelName) == NULL) {
    channels.addChannel(channelName, Channel(channelName));
	channels.addOperator(channelName, clients.getClient(idClient));
  }
  channels.addUser(channelName, clients.getClient(idClient));

  std::set<int> users = channels.getUsers(channelName);
  std::set<int>::iterator it = users.begin();
  while (it != users.end()) {
    std::cout << "user : " << *it << " is in " << channelName << std::endl;
    it++;
  }

  //   if (!channel->getTopic().empty()) {
  //     clients.sendMessage("rpl_332"); // RPL_TOPIC
  //   }

  //   clients.sendMessage("rpl_353"); // RPL_NAMREPLY
  //   clients.sendMessage("rpl_366"); // RPL_ENDOFNAMES
}