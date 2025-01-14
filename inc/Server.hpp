/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:09:29 by gbruscan          #+#    #+#             */
/*   Updated: 2025/01/14 17:57:53 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <map>
# include <poll.h>
# include <string>
# include "Command.hpp"

struct	Client;

class Server
{
  private:
	int server_fd;
	int epoll_fd; // Descripteur pour epoll
	int port;
	std::string password;
	std::map<int, Client *> _clients; // Gestion des clients connectés
    ClientManager _clientManager;
    ChannelManager _channelManager;

  public:
	Server(int port, const std::string &password);
	~Server();
	void run();
	void setupSocket();
	void acceptNewClient();
	void handleClientMessage(int fd);
	void dispatchCommand(ClientManager& clients, ChannelManager& channels,
                     const TokenisedCommand &cmd, const int fd);
	void handleInvalidCommand(ClientManager& clients, const std::string &cmd,
                          const int fd);


	// cccccccccccccccccc
	//
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

   bool validateNick(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
   bool validateUser(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
   bool validateJoin(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
   bool validatePrivmsg(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
  bool validateQuit(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
  bool validatePing(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
  bool validateKick(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
  bool validateMode(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
  bool validatePass(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
  bool validateTopic(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);
  bool validatePart(ClientManager& clients, ChannelManager& channels,
                    const TokenisedCommand &cmd, const int fd);

  void doNick(ClientManager& clients, ChannelManager channels,
              const TokenisedCommand &cmd, const int fd);
  void doUser(ClientManager& clients, ChannelManager channels,
              const TokenisedCommand &cmd, const int fd);
  void doJoin(ClientManager& clients, ChannelManager& channels,
              const TokenisedCommand &cmd, int fdClient);
  void doPrivMsg(ClientManager& clients, ChannelManager& channels,
      const TokenisedCommand &cmd, const int idClient);
  void doQuit(ClientManager& clients, ChannelManager& channels,
              const TokenisedCommand &cmd, const int fd);
  void doPing(ClientManager& clients, ChannelManager& channels,
            const TokenisedCommand &cmd, int fdClient);
  void doPong(ClientManager& clients, ChannelManager& channels,
            const TokenisedCommand &cmd, int fdClient);
  void doKick(ClientManager& clients, ChannelManager& channels,
              const TokenisedCommand &cmd, const int fd);
  void doMode(ClientManager& clients, ChannelManager& channels,
              const TokenisedCommand &cmd, const int fd);
  void doPass(ClientManager& clients, ChannelManager& channels,
              const TokenisedCommand &cmd, const int fd);
  void doTopic(ClientManager& clients, ChannelManager& channels,
               const TokenisedCommand &cmd, const int fd);
  void doPart(ClientManager& clients, ChannelManager& channels,
              const TokenisedCommand &cmd, const int fd);
};

#endif
