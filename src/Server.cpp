/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:09:05 by gbruscan          #+#    #+#             */
/*   Updated: 2025/01/14 21:40:09 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <map>
#include <sstream>
#include "Client.hpp"
#include "Tokenisation.hpp"
#include "Command.hpp"

struct Client;

const std::vector<std::string> &CommandList::getCommands() {
  static std::vector<std::string> commands;
  if (commands.empty()) {
    commands.push_back("NICK");
    commands.push_back("USER");
    commands.push_back("JOIN");
    commands.push_back("PRIVMSG");
    commands.push_back("QUIT");
    commands.push_back("PING");
    commands.push_back("KICK");
    commands.push_back("MODE");
    commands.push_back("PASS");
    commands.push_back("TOPIC");
    commands.push_back("PART");
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

void Server::dispatchCommand(ClientManager& clients, ChannelManager& channels,
                     const TokenisedCommand &cmd, const int fd) {
  int commandIndex = CommandList::findCommandIndex(cmd.getCommand());

  // Handle CAP command separately as it's not in our main command list
  if (cmd.getCommand() == "CAP") {
    // Just acknowledge CAP LS for now
    if (cmd.getArguments().size() > 0 && cmd.getArguments()[0] == "LS") {
      std::string response = "CAP * LS :\r\n";
      send(fd, response.c_str(), response.length(), 0);
    }
    return;
  }

  switch (commandIndex) {
  case 0: // NICK
    if (validateNick(clients, channels, cmd, fd)) {
      clients.setNickname(fd, cmd.getArguments()[0]);
    }
    break;

  case 1: // USER
    if (validateUser(clients, channels, cmd, fd)) {
      clients.setClientname(fd, cmd.getArguments()[0]);
      clients.setHostname(fd, cmd.getArguments()[2]);
    }
    break;

  case 2: // JOIN
    if (validateJoin(clients, channels, cmd, fd)) {
      doJoin(clients, channels, cmd, fd);
    }
    break;

  case 3: // PRIVMSG
    if (validatePrivmsg(clients, channels, cmd, fd)) {
      doPrivMsg(clients, channels, cmd, fd);
    }
    break;

  case 4: // QUIT
    if (validateQuit(clients, channels, cmd, fd)) {
      // doQuit();
    }
    break;

  case 5: // PING
    if (validatePing(clients, channels, cmd, fd)) {
      std::string response = "PONG :" + cmd.getArguments()[0] + "\r\n";
      send(fd, response.c_str(), response.length(), 0);
    }
    break;

  case 6: // KICK
    if (validateKick(clients, channels, cmd, fd)) {
      // doKick();
    }
    break;

  case 7: // MODE
    if (validateMode(clients, channels, cmd, fd)) {
      // doMode();
    }
    break;

  case 8: // PASS
    if (validatePass(clients, channels, cmd, fd)) {
      clients.setAuthenticated(fd, true);
      doPass(clients, channels, cmd, fd);
    }
    break;

  case 9: // TOPIC
    if (validateTopic(clients, channels, cmd, fd)) {
      // doTopic();
    }
    break;

  case 10: // PART
    if (validatePart(clients, channels, cmd, fd)) {
      // doPart();
    }
    break;

  default:
    handleInvalidCommand(clients, cmd.getCommand(), fd);
    break;
  }
}

void Server::handleInvalidCommand(ClientManager& clients, const std::string &cmd,
                          const int fd) {
  std::string response = "421 " + clients.getNickname(fd) + " " + cmd + " :Unknown command\r\n";
  send(fd, response.c_str(), response.length(), 0);
}


Server::Server(int port,const std::string& password)
    : port(port), password(password)
{
    setupSocket();
}

Server::~Server()
{
	close(server_fd);
	close(epoll_fd); // Fermeture de epoll_fd
}

void Server::setupSocket()
{
	int					opt;
	struct sockaddr_in	server_addr;
	struct epoll_event	server_event;

	// Creation de la socket serveur
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	// Option de reutilisation des adresses
	opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	// Mode non-bloquant pour la socket serveur
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
	// Configuration de l'adresse du serveur
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	if (bind(server_fd, (struct sockaddr *)&server_addr,
			sizeof(server_addr)) < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, SOMAXCONN) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	// Creation de epoll_fd
	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}
	// Ajouter la socket serveur à epoll
	server_event.events = EPOLLIN; // Lecture
	server_event.data.fd = server_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &server_event) == -1)
	{
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}
}

void Server::run()
{
	struct epoll_event	events[10];
	int					ret;

	while (true)
	{
		// Attendre les evenements sur les descripteurs
		ret = epoll_wait(epoll_fd, events, 10, -1); // 10 evenements max à gerer
		if (ret < 0)
		{
			perror("epoll_wait");
			continue ;
		}
		for (int i = 0; i < ret; ++i)
		{
			if (events[i].data.fd == server_fd)
			{
				// Accepter un nouveau client
				acceptNewClient();
			}
			else
			{
				// Gerer les messages du client
				handleClientMessage(events[i].data.fd);
			}
		}
	}
}

void Server::acceptNewClient()
{
	struct sockaddr_in	client_addr;
	socklen_t			addr_len;
	int					client_fd;
	struct epoll_event	client_event;
	Client				*newClient;

	addr_len = sizeof(client_addr);
	// Accepter la connexion
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client_fd < 0)
	{
		perror("accept");
		return ;
	}
	// Mode non-bloquant pour le client
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("fcntl");
		close(client_fd);
		return ;
	}
	// Ajouter le client à epoll
	client_event.events = EPOLLIN; // Lecture
	client_event.data.fd = client_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1)
	{
		perror("epoll_ctl");
		close(client_fd);
		return ;
	}
	// Créer un objet Client pour gérer les informations
	newClient = new Client(client_fd);
	newClient->hostname = (inet_ntoa(client_addr.sin_addr));
	// Ajouter le client au conteneur de gestion (map)
	_clients[client_fd] = newClient;
	std::cout << "Nouveau client connecté : " << newClient->hostname << std::endl;
    _clientManager.addClient(newClient);
}

void Server::handleClientMessage(int fd)
{
	char buffer[512];
	int bytes_received = recv(fd, buffer, sizeof(buffer) - 1, 0);

	if (bytes_received <= 0)
	{
		std::cout << "Client déconnecté (fd: " << fd << ")" << std::endl;
		close(fd);
		epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
		delete _clients[fd];
		_clients.erase(fd);
		return;
	}

	buffer[bytes_received] = '\0';
	std::string message(buffer);
	TokenisedCommand cmd = tokenize(message);
	Client* client = _clientManager.getClient(fd);

	std::cout << buffer << std::endl;
	std::stringstream ss(message);
	std::string token;

	dispatchCommand(_clientManager, _channelManager, cmd, fd);
	//Gérer PASS
	// if (message.find("CAP LS") != std::string::npos)
	// {
	// 	std::string capMsg = "CAP * LS :multi-prefix sasl\r\n";
	// 	send(fd, capMsg.c_str(), capMsg.size(), 0);
	// 	std::cout << "Réponse CAP LS envoyée." << std::endl;
	// }
	if (!client->isAuthenticated)
	{
		if (message.find("PASS ") != std::string::npos)
		{
			std::string pass;
			while (ss >> token)
			{
				if (token == "PASS")
				{
					ss >> token;
					pass = token;
					break;
				}
			}
			if (pass == password)
			{
				client->isAuthenticated = true;
				std::cout << "Mot de passe correct pour le client (fd: " << fd << ")" << std::endl;
			}
			else
			{
				std::string errorMsg = "ERROR :Mot de passe incorrect\r\n";
				send(fd, errorMsg.c_str(), errorMsg.size(), 0);
				close(fd);
				epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
				delete _clients[fd];
				_clients.erase(fd);
				return;
			}
		}
		else
		{
			std::string errorMsg = "ERROR :Mot de passe requis\r\n";
			send(fd, errorMsg.c_str(), errorMsg.size(), 0);
			return;
		}
	}

	// Gérer NICK
	if (message.find("NICK ") != std::string::npos)
	{
		std::string nick;
		while (ss >> token)
		{
			if (token == "NICK")
			{
				ss >> token;
				nick = token;
				break;
			}
		}
		client->nickname = nick;
		std::cout << "Client a défini son pseudonyme : " << nick << std::endl;
	}

	// Gérer USER
	if (message.find("USER ") != std::string::npos)
	{
		if (client->nickname.empty())
		{
			std::string errorMsg = "ERROR :Vous devez définir un pseudonyme avec NICK avant USER\r\n";
			send(fd, errorMsg.c_str(), errorMsg.size(), 0);
			return;
		}
		// Envoyer le message de bienvenue
		std::string welcomeMsg =
			":localhost 001 " + client->nickname + " :Welcome to the IRC server\r\n" +
			":localhost 002 " + client->nickname + " :Your host is localhost, running version 1.0\r\n" +
			":localhost 003 " + client->nickname + " :This server was created today\r\n" +
			":localhost 004 " + client->nickname + " localhost 1.0 i\r\n";

		send(fd, welcomeMsg.c_str(), welcomeMsg.size(), 0);
	}
	//std::string modeMsg = ":" + client->nickname + " MODE " + client->nickname + " +i\r\n";
	//send(fd, modeMsg.c_str(), modeMsg.size(), 0);
	if (message.find("PING ") != std::string::npos)
	{
		std::string token;
		ss >> token;  // Lire le "PING"
		ss >> token;  // Lire le serveur ciblé après "PING"
		if (!token.empty())
		{
			std::string response = "PONG :" + token + "\r\n";
			send(fd, response.c_str(), response.size(), 0);
			std::cout << "Send PONG response : " + response << std::endl;
		}
	}
	if (message.find("QUIT ") != std::string::npos)
	{

    }
}
