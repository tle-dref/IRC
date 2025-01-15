/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:09:29 by gbruscan          #+#    #+#             */
/*   Updated: 2025/01/15 22:28:27 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Errors.hpp"
#include "Tokenisation.hpp"
#include <poll.h>
#include <string>
#include <vector>

struct Client;

class Server {
private:
  int server_fd;
  int epoll_fd; // Descripteur pour epoll
  int port;
  std::string password;
  ClientManager _clients;
  ChannelManager _channels;

public:
  Server(int port, const std::string &password);
  ~Server();
  void run();
  void setupSocket();
  void acceptNewClient();
  void handleClientMessage(int fd);
  void handleClientMessage(const std::string &message, int fd);
  void dispatchCommand(ClientManager &clients, ChannelManager &channels,
                       const TokenisedCommand &cmd, const int fd);
  void handleInvalidCommand(ClientManager &clients, const std::string &cmd,
                            const int fd);

  // cccccccccccccccccc
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

  // Commandes
  static const std::vector<std::string> &getCommands();
  bool validateNick(const TokenisedCommand &cmd, int fd);
  void doNick(const TokenisedCommand &cmd, int fd);
  bool validateUser(const TokenisedCommand &cmd, int fd);
  void doUser(const TokenisedCommand &cmd, int fd);
  bool validatePass(const TokenisedCommand &cmd, int fd);
  void doPass(const TokenisedCommand &cmd, int fd);
  bool validateCap(const TokenisedCommand &cmd, int fd);
  void doCap(const TokenisedCommand &cmd, int fd);
  bool validatePing(const TokenisedCommand &cmd, int fd);
  void doPong(const TokenisedCommand &cmd, int fd);
  bool validateQuit(const TokenisedCommand &cmd, int fd);
  void doQuit(const TokenisedCommand &cmd, int fd);
  bool validatePrivmsg(const TokenisedCommand &cmd, int fd);
  void doPrivmsg(const TokenisedCommand &cmd, int fd);
  bool validateJoin(const TokenisedCommand &cmd, int fd);
  void doJoin(const TokenisedCommand &cmd, int fd);
  bool validatePart(const TokenisedCommand &cmd, int fd);
  void doPart(const TokenisedCommand &cmd, int fd);
  bool validateKick(const TokenisedCommand &cmd, int fd);
  void doKick(const TokenisedCommand &cmd, int fd);
  bool validateMode(const TokenisedCommand &cmd, int fd);
  void doMode(const TokenisedCommand &cmd, int fd);
  bool validateTopic(const TokenisedCommand &cmd, int fd);
  void doTopic(const TokenisedCommand &cmd, int fd);
};

#endif
