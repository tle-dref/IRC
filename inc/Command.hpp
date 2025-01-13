#pragma once
#include "Client.hpp"
#include "Tokenisation.hpp"
#include <string>
#include <vector>

class CommandList {
public:
  static const std::vector<std::string> &getCommands();
  static int findCommandIndex(const std::string &cmd);
};

class CommandHandler {
private:
  ClientManager &_clientManager;
  ChannelManager &_channelManager;

public:
  CommandHandler(ClientManager &clientMgr, ChannelManager &chanMgr)
      : _clientManager(clientMgr), _channelManager(chanMgr) {}

  // Commandes d'authentification
  void handleNick(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);
  void handleUser(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);
  void handlePass(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);

  // Commandes de gestion de channels
  void handleJoin(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);
  void handlePart(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);
  void handleTopic(int clientFd, const std::vector<std::string> &args,
                   ClientManager &userManager, ChannelManager &channelManager);
  void handleMode(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);

  // Commandes de messagerie
  void handlePrivmsg(int clientFd, const std::vector<std::string> &args,
                     ClientManager &userManager,
                     ChannelManager &channelManager);
  void handleNotice(int clientFd, const std::vector<std::string> &args,
                    ClientManager &userManager, ChannelManager &channelManager);

  // Commandes de gestion
  void handleKick(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);
  void handleInvite(int clientFd, const std::vector<std::string> &args,
                    ClientManager &userManager, ChannelManager &channelManager);
  void handleQuit(int clientFd, const std::vector<std::string> &args,
                  ClientManager &userManager, ChannelManager &channelManager);
  void handleMsg(int clientFd, const std::vector<std::string> &args,
                 ClientManager &userManager, ChannelManager &channelManager);
};

void dispatchCommand(ClientManager clients, const TokenisedCommand &cmd);
void handleInvalidCommand(ClientManager clients, const std::string &cmd);

void validateNick(ClientManager clients, const TokenisedCommand &cmd);
void validateUser(ClientManager clients, const TokenisedCommand &cmd);
void validateJoin(ClientManager clients, const TokenisedCommand &cmd);
void validatePrivMsg(ClientManager clients, const TokenisedCommand &cmd);
void validateQuit(ClientManager clients, const TokenisedCommand &cmd);
void validatePing(ClientManager clients, const TokenisedCommand &cmd);
void validatePong(ClientManager clients, const TokenisedCommand &cmd);
