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

int CommandList::findCommandIndex(const std::string &command) {
  const std::vector<std::string> &commands = getCommands();
  for (size_t i = 0; i < commands.size(); ++i) {
    if (commands[i] == command) {
      return i;
    }
  }
  return -1;
}

void dispatchCommand(ClientManager client, const TokenisedCommand &cmd) {
  int commandIndex = CommandList::findCommandIndex(cmd.getCommand());

  switch (commandIndex) {
  case 0: // NICK
    validateNick(client, cmd);
    // doNick();
    break;

  case 1: // USER
    validateUser(client, cmd);
    // doUser();
    break;

  case 2: // JOIN
    validateJoin(client, cmd);
    // doJoin();
    break;

  case 3: // PRIVMSG
    validatePrivMsg(client, cmd);
    // doPrivMsg();
    break;

  case 4: // QUIT
    validateQuit(client, cmd);
    // doQuit();
    break;

  case 5: // PING
    validatePing(client, cmd);
    // doPing();
    break;

  case 6: // PONG
    validatePong(client, cmd);
    // doPong();
    break;

  default:
    handleInvalidCommand(client, cmd.getCommand());
    break;
  }
}

void handleInvalidCommand(ClientManager client, const std::string &command) {
  throw std::runtime_error("error_421");
  (void)client;
  (void)command;
}

void validateNick(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty()) {
    throw std::runtime_error("error_431");
  }
  const std::string &nickname = cmd.getArguments()[0];
  if (nickname.length() > 9 || !isalpha(nickname[0])) {
    throw std::runtime_error("error_432");
  }
  if (client.usernameExists(nickname)) {
    throw std::runtime_error("error_433");
  }
}

void validateUser(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 4)
    throw std::runtime_error("error_461"); // ERR_NEEDMOREPARAMS

  //   if (client.isRegister())
  //     throw std::runtime_error("error_462");

  (void)client;
}

void validateJoin(ClientManager client, const TokenisedCommand &cmd) {
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

  //   if (channel->isBanned(client.getNickname())) {
  //     throw std::runtime_error("error_474"); // ERR_BANNEDFROMCHAN
  //   }

  //   if (channel->isFull()) {
  //     throw std::runtime_error("error_471"); // ERR_CHANNELISFULL
  //   }

  //   if (channel->isInviteOnly() && !channel->isInvited(client.getNickname()))
  //   {
  //     throw std::runtime_error("error_473"); // ERR_INVITEONLYCHAN
  //   }

  //   if (channel->hasKey() && !channel->checkKey(cmd.getArguments()[1])) {
  //     throw std::runtime_error("error_475"); // ERR_BADCHANNELKEY
  //   }

  //   if (client.getJoinedChannelsCount() >= server.getMaxChannelsPerUser()) {
  //     throw std::runtime_error("error_405"); // ERR_TOOMANYCHANNELS
  //   }

  //   channel->addUser(client);

  //   if (!channel->getTopic().empty()) {
  //     client.sendMessage("rpl_332"); // RPL_TOPIC
  //   }

  //   client.sendMessage("rpl_353"); // RPL_NAMREPLY
  //   client.sendMessage("rpl_366"); // RPL_ENDOFNAMES

  (void)client;
}

void validatePrivMsg(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().size() < 2)
    throw std::runtime_error("error_412");
  (void)client;
}

void validateQuit(ClientManager client, const TokenisedCommand &cmd) {
  (void)client;
  (void)cmd;
}

void validatePing(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_409");
  (void)client;
}

void validatePong(ClientManager client, const TokenisedCommand &cmd) {
  if (cmd.getArguments().empty())
    throw std::runtime_error("error_409");
  (void)client;
}