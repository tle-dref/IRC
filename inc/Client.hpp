#pragma once
#include "Channel.hpp"
#include <iostream>
#include <map>

struct Channel;

struct Client {
  int fd;               // File descriptor pour l'utilisateur
  std::string nickname; // Pseudo de l'utilisateur
  std::string username; // Nom d'utilisateur
  std::string hostname; // Hôte de l'utilisateur
  bool isAuthenticated; // Statut d'authentification

  Client();
  Client(int fd);
  Client(std::string nickname);
  ~Client();
};

class ClientManager {
private:
  std::map<int, Client> _clients;

public:
  ClientManager(){};
  virtual ~ClientManager(){};

  // functions
  void addClient(Client user);
  void removeClient(int fd);
  void sendToAllUsers(Channel *channel, std::string message); // TODO
  void sendPrvMsg(Client *client, std::string message);       // TODO
  void printClient(int fd) const; // Affiche les informations d'un client donné
  void printClients() const;

  // getter
  int getFd(std::string username);
  std::string getNickname(int fd);
  std::string getClientname(int fd);
  std::string getHostname(int fd);
  Client *getClient(int fd);
  const std::map<int, Client> &getClients() const;
  void updateNickname(int fd, std::string nickname);

  // setter
  void setAuthenticated(int fd, bool isAuthenticated);
  void setNickname(int fd, std::string nickname);
  void setClientname(int fd, std::string username);
  void setHostname(int fd, std::string hostname);

  // check
  bool isOperator(int fd);
  bool userExists(int fd);
  bool nicknameExists(std::string nickname);
  bool usernameExists(std::string username);
  bool isAuthenticated(int fd);
};