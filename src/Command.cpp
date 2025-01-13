#include "Command.hpp"
#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>

const std::vector<std::string> &CommandList::getCommands() {
  static std::vector<std::string> commands;
  if (commands.empty()) {
    commands.push_back("NICK");
    commands.push_back("USER");
    commands.push_back("JOIN");
    commands.push_back("PRIVMSG");
    commands.push_back("QUIT");
    commands.push_back("PING");
    commands.push_back("PONG");
  }
  return commands;
}

int CommandList::findCommandIndex(const std::string &cmd) {
  const std::vector<std::string> &cmds = getCommands();
  for (size_t i = 0; i < cmds.size(); ++i) {
    if (cmds[i] == cmd) {
      return i;
    }
  }
  return -1;
}

void dispatchCommand(ClientManager clients, const TokenisedCommand &cmd) {
  int commandIndex = CommandList::findCommandIndex(cmd.getCommand());

  switch (commandIndex) {
  case 0: // NICK
    validateNick(clients, cmd);
    // doNick();
    break;

  case 1: // USER
    validateUser(clients, cmd);
    // doUser();
    break;

  case 2: // JOIN
    validateJoin(clients, cmd);
    // doJoin();
    break;

  case 3: // PRIVMSG
    validatePrivMsg(clients, cmd);
    // doPrivMsg();
    break;

  case 4: // QUIT
    validateQuit(clients, cmd);
    // doQuit();
    break;

  case 5: // PING
    validatePing(clients, cmd);
    // doPing();
    break;

  case 6: // PONG
    validatePong(clients, cmd);
    // doPong();
    break;

  default:
    handleInvalidCommand(clients, cmd.getCommand());
    break;
  }
}

void handleInvalidCommand(ClientManager clients, const std::string &cmd) {
  throw std::runtime_error("error_421");
  (void)clients;
  (void)cmd;
}

void validateNick(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty()) {
    throw std::runtime_error("error_431");
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (nickname.length() > 9 || !isalpha(nickname[0])) {
    throw std::runtime_error("error_432");
  }
  if (clients.usernameExists(nickname)) {
    throw std::runtime_error("error_433");
  }
}

void validateUser(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 4)
    throw std::runtime_error("error_461"); // ERR_NEEDMOREPARAMS

  // if (clients.isRegister())
  //   throw std::runtime_error("error_462"); // ERR_ALREADYREGISTERED

  (void)clients;
}

void validateJoin(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_461");

  const std::string &channelName = cmd.getArguments()[0];

  if (channelName.empty() || channelName[0] != '#' ||
      channelName.length() > 50) {
    throw std::runtime_error("error_476"); // ERR_BADCHANMASK
  }

  //   Channel *channel = server.findChannel(channelName);

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
}

void validatePrivMsg(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 2)
    throw std::runtime_error("error_412");
  (void)clients;
}

void validateQuit(ClientManager clients, const TokenisedCommand &cmd) {
  (void)clients;
  (void)cmd;
}

void validatePing(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_409");
  (void)clients;
}

void validatePong(ClientManager clients, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_409");
  (void)clients;
}