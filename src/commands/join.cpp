#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool validateJoin(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient) {
  if (cmd.getArguments().empty()) {
    std::cerr << "error_461 : ERR_NEEDMOREPARAMS" << std::endl;
    return false;
  }

  const std::string &channelName = cmd.getArguments()[0];

  if (channelName.empty() || channelName[0] != '#' ||
      channelName.length() > 50) {
    std::cerr << "error_476 : ERR_BADCHANMASK" << std::endl;
    return false;
  }

  // Channel *channel = server.findChannel(channelName);

  //   if (!channel) {
  //     throw std::runtime_error("error_403"); // ERR_NOSUCHCHANNEL
  //   }

  //   if (channel->isBanned(clients.getNickname())) {
  //     throw std::runtime_error("error_474"); // ERR_BANNEDFROMCHAN
  //   }

  //   if (channel->isFull()) {
  //     throw std::runtime_error("error_471"); // ERR_CHANNELISFULL
  //   }

  //   if (channel->isInviteOnly() &&
  //   !channel->isInvited(clients.getNickname()))
  //   {
  //     throw std::runtime_error("error_473"); // ERR_INVITEONLYCHAN
  //   }

  //   if (channel->hasKey() && !channel->checkKey(cmd.getArguments()[1])) {
  //     throw std::runtime_error("error_475"); // ERR_BADCHANNELKEY
  //   }

  //   if (clients.getJoinedChannelsCount() >= server.getMaxChannelsPerUser()) {
  //     throw std::runtime_error("error_405"); // ERR_TOOMANYCHANNELS
  //   }

  //   channel->addUser(clients);

  //   if (!channel->getTopic().empty()) {
  //     clients.sendMessage("rpl_332"); // RPL_TOPIC
  //   }

  //   clients.sendMessage("rpl_353"); // RPL_NAMREPLY
  //   clients.sendMessage("rpl_366"); // RPL_ENDOFNAMES

  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}