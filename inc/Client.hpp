#pragma once
#include "Channel.hpp"
#include <iostream>
#include <map>

struct Channel;

struct Client {
  int id;               // ID unique of the client
  int fd;               // File descriptor pour l'utilisateur
  std::string nickname; // Pseudo de l'utilisateur
  std::string username; // Nom d'utilisateur
  std::string hostname; // Hôte de l'utilisateur
  bool isAuthenticated; // Statut d'authentification

  Client();
  Client(int fd);
  Client(std::string nickname);
  ~Client();
  int idGenerator();
};

class ClientManager {
private:
  std::map<int, Client> _clients;

public:
  ClientManager(){};
  virtual ~ClientManager(){};

  // functions
  void addClient(Client user);
  void removeClient(int id);
  void sendToAllUsers(Channel *channel, std::string message); // TODO
  void sendPrvMsg(Client *client, std::string message);       // TODO
  void printClient(int id) const; // Affiche les informations d'un client donné
  void printClients() const;

  // getter
  int getFd(std::string username);
  std::string getNickname(int id);
  std::string getClientname(int id);
  std::string getHostname(int id);
  Client *getClient(int id);
  const std::map<int, Client> &getClients() const;
  void updateNickname(int id, std::string nickname);

  // setter
  void setAuthenticated(int id, bool isAuthenticated);
  void setNickname(int id, std::string nickname);
  void setClientname(int id, std::string username);
  void setHostname(int id, std::string hostname);

  // check
  bool isOperator(int id);
  bool userExists(int id);
  bool nicknameExists(std::string nickname);
  bool usernameExists(std::string username);
  bool isAuthenticated(int id);
};