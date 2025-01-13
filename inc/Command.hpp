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

void dispatchCommand(ClientManager clients, ChannelManager channels,
                     const TokenisedCommand &cmd, const int idClient);
void handleInvalidCommand(ClientManager clients, const std::string &cmd,
                          const int idClient);

bool validateNick(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validateUser(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validateJoin(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validatePrivMsg(ClientManager clients, ChannelManager channels,
                     const TokenisedCommand &cmd, const int idClient);
bool validateQuit(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validatePong(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validateKick(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validateMode(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validatePass(ClientManager clients, ChannelManager channels,
                  const TokenisedCommand &cmd, const int idClient);
bool validateTopic(ClientManager clients, ChannelManager channels,
                   const TokenisedCommand &cmd, const int idClient);
bool validatePart(ClientManager clients, ChannelManager channels,
                   const TokenisedCommand &cmd, const int idClient);
