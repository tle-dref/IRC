/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:09:05 by gbruscan          #+#    #+#             */
/*   Updated: 2025/01/16 23:20:34 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/epoll.h>
#include <unistd.h>
#include <signal.h>

struct Client;

static bool sigStop = false;

const std::vector<std::string> &Server::getCommands() {
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
    commands.push_back("CAP");
    commands.push_back("INVITE");
  }
  return (commands);
}

void Server::dispatchCommand(ClientManager &clients, ChannelManager &channels,
                             const TokenisedCommand &cmd, const int fd) {
  (void)channels;
  const std::string &command = cmd.getCommand();
  if (command == "NICK") {
    if (validateNick(cmd, fd))
      doNick(cmd, fd);
  } else if (command == "USER") {
    if (validateUser(cmd, fd))
      doUser(cmd, fd);
  } else if (command == "JOIN") {
    if (validateJoin(cmd, fd))
      doJoin(cmd, fd);
  } else if (command == "PRIVMSG") {
    if (validatePrivmsg(cmd, fd))
      doPrivmsg(cmd, fd);
  } else if (command == "QUIT") {
    if (validateQuit(cmd, fd))
      doQuit(cmd, fd);
  } else if (command == "PING") {
    if (validatePing(cmd, fd))
      doPong(cmd, fd);
  } else if (command == "KICK") {
    if (validateKick(cmd, fd))
      doKick(cmd, fd);
  } else if (command == "MODE") {
    if (validateMode(cmd, fd))
      doMode(cmd, fd);
  } else if (command == "PASS") {
    if (validatePass(cmd, fd))
      doPass(cmd, fd);
  } else if (command == "TOPIC") {
    if (validateTopic(cmd, fd))
      doTopic(cmd, fd);
  } else if (command == "PART") {
    if (validatePart(cmd, fd))
      doPart(cmd, fd);
  } else if (command == "CAP") {
    if (validateCap(cmd, fd))
      doCap(cmd, fd);
  } else if (command == "INVITE") {
    if (validateInvite(cmd, fd))
      doInvite(cmd, fd);
  } else {
    handleInvalidCommand(clients, command, fd);
  }
}

void Server::handleInvalidCommand(ClientManager &clients,
                                  const std::string &cmd, const int fd) {
  std::string response =
      "421 " + clients.getNickname(fd) + " " + cmd + " :Unknown command\n";
  send(fd, response.c_str(), response.length(), MSG_NOSIGNAL);
}

Server::Server(int port, const std::string &password)
    : port(port), password(password) {
  setupSocket();
}

Server::~Server() {
  close(server_fd);
  close(epoll_fd); // Fermeture de epoll_fd
  if (!_clients.getClients().empty())
  {
      std::map<int, Client *>::iterator it = _clients.getClients().begin();
      for (; it != _clients.getClients().end(); ++it)
      {
          if (_clients.userExists(it->first))
          {
            std::cout << "Client déconnecté (fd: " << it->first << ")" << std::endl;
            close(it->first);
            if (it->second)
                delete it->second;
          }
      }
  }
}

void Server::createBot() {
  Client *bot;

  bot = new Client();
  bot->fd = 1000;
  bot->nickname = "bot";
  bot->username = "bot";
  bot->hostname = "localhost";
  bot->realname = "Bot du serveur IRC";
  bot->isAuthenticated = true;
  _clients.addClient(bot);
}

void Server::setupSocket() {
  int opt;
  struct sockaddr_in server_addr;
  struct epoll_event server_event;

  // Creation de la socket serveur
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  // Option de reutilisation des adresses
  opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  // Mode non-bloquant pour la socket serveur
  if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0) {
    perror("fcntl");
    exit(EXIT_FAILURE);
  }
  // Configuration de l'adresse du serveur
  std::memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, SOMAXCONN) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  // Creation de epoll_fd
  epoll_fd = epoll_create1(0);
  if (epoll_fd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }
  // Ajouter la socket serveur à epoll
  server_event.events = EPOLLIN; // Lecture
  server_event.data.fd = server_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &server_event) == -1) {
    perror("epoll_ctl");
    exit(EXIT_FAILURE);
  }
}

void Server::run() {
  struct epoll_event events[10];
  int ret;

  createBot();
	signal(SIGINT, Server::sigInt_Hdl);

	while (sigStop == 0) {
    // Attendre les evenements sur les descripteurs
    ret = epoll_wait(epoll_fd, events, 10, -1); // 10 evenements max à gerer
    if (ret < 0) {
      perror("epoll_wait");
      continue;
    }
    for (int i = 0; i < ret; ++i) {
      if (events[i].data.fd == server_fd) {
        // Accepter un nouveau client
        acceptNewClient();
      } else {
        // Gerer les messages du client
        handleClientMessage(events[i].data.fd);
      }
    }
  }
}

void Server::acceptNewClient() {
  struct sockaddr_in client_addr;
  socklen_t addr_len;
  int client_fd;
  struct epoll_event client_event;
  Client *newClient;

  addr_len = sizeof(client_addr);
  // Accepter la connexion
  client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
  if (client_fd < 0) {
    perror("accept");
    return;
  }
  // Mode non-bloquant pour le client
  if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0) {
    perror("fcntl");
    close(client_fd);
    return;
  }
  // Ajouter le client à epoll
  client_event.events = EPOLLIN; // Lecture
  client_event.data.fd = client_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) {
    perror("epoll_ctl");
    close(client_fd);
    return;
  }
  // Créer un objet Client pour gérer les informations
  newClient = new Client(client_fd);
  newClient->hostname = (inet_ntoa(client_addr.sin_addr));
  _clients.addClient(newClient);
  std::cout << "Nouveau client connecté : " << newClient->hostname << std::endl;
}

void Server::handleClientMessage(int fd) {
  char buffer[512];
  int bytes_received;

  bytes_received = recv(fd, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received <= 0) {
    std::cout << "Client déconnecté (fd: " << fd << ")" << std::endl;
    close(fd);
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
    // delete _clients[fd];
    _clients.removeClient(fd);
    return;
  }
  buffer[bytes_received] = '\0';
  std::string message(buffer);
  // Ajouter \r\n si nécessaire
  if (message.length() >= 2 && message.substr(message.length() - 2) != "\r\n") {
    message += "\r\n";
  }
  handleClientMessage(message, fd);
}

void Server::handleClientMessage(const std::string &message, int fd) {
  TokenisedCommand cmd;
  Client *client;

  std::stringstream ss(message);
  std::string line;
  while (std::getline(ss, line, '\n')) {
    if (line.empty())
      continue;
    cmd = tokenize(line);
    if (cmd.isValid()) {
      std::cout << "Processing line: " << line << std::endl;
      cmd.print();
      std::cout << std::endl;
      // Récupérer le client une seule fois
      client = _clients.getClient(fd);
      if (client == NULL) {
        std::cerr << "Erreur : Client avec fd " << fd << " non trouvé."
                  << std::endl;
        continue;
      }
      // Vérifier l'authentification sauf pour les commandes CAP et PASS
      if (cmd.getCommand() != "CAP" && cmd.getCommand() != "PASS" &&
          !client->isAuthenticated) {
        std::string errorMsg =
            "ERROR :Vous devez d'abord vous authentifier avec PASS\n";
        if (send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL) == -1) {
          std::cerr
              << "Erreur : Échec de l'envoi du message d'erreur au client fd "
              << fd << std::endl;
        }
        continue;
      }
      dispatchCommand(_clients, _channels, cmd, fd);
    }
  }
}

void    Server::sigInt_Hdl(int signo)
{
    if (signo == SIGINT)
	{
        sigStop = true;
		std::cerr << "\b\b  \b\b" << std::endl; // flex pour effacer ^C
	}
}
