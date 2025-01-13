#pragma once
#include <iostream>
#include <map>

struct Client {
  int fd;               // File descriptor pour l'utilisateur
  std::string nickname; // Pseudo de l'utilisateur
  std::string username; // Nom d'utilisateur
  std::string hostname; // Hôte de l'utilisateur
  bool isOperator;      // Statut d'opérateur
  bool isAuthenticated; // Statut d'authentification
};

class ClientManager {
private:
  std::map<int, Client> _clients;

public:
  ClientManager() {
    // Création d’un client par défaut
    Client defaultClient;
    defaultClient.fd = 1;
    defaultClient.nickname = "DefaultNick";
    defaultClient.username = "defaultUser";
    defaultClient.hostname = "localhost";
    defaultClient.isOperator = false;
    defaultClient.isAuthenticated = false;
    _clients.insert(std::make_pair(defaultClient.fd, defaultClient));
  }
  virtual ~ClientManager(){};
  //   // functions
  //   void addClient(int fd, Client user);
  //   void removeClient(int fd);
  //   Client *getClient(int fd);
  //   // getter
  //   int getFd(std::string username);
  //   std::string getNickname(int fd);
  //   std::string getClientname(int fd);
  //   std::string getHostname(int fd);
  //   const std::map<int, Client> &getClients() const;
  //   void updateNickname(int fd, std::string nickname);
  //   // setter
  //   void setAuthenticated(int fd, bool isAuthenticated);
  //   void setOperator(int fd, bool isOperator);
  //   void setNickname(int fd, std::string nickname);
  //   void setClientname(int fd, std::string username);
  //   void setHostname(int fd, std::string hostname);
  //   // check
  //   bool isOperator(int fd);
  //   bool userExists(int fd);
  //   bool nicknameExists(std::string nickname);
  //   bool usernameExists(std::string username);
  //   bool isAuthenticated(int fd);
};