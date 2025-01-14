#include "Client.hpp"

Client::Client()
    : fd(-1), nickname(""), username(""), hostname(""),
      isAuthenticated(false) {}

Client::Client(int fd) : fd(fd), nickname(""), username(""), hostname(""),
      isAuthenticated(false) {}

Client::Client(std::string nickname)
    : nickname(nickname), username(""), hostname(""),
      isAuthenticated(false) {}

Client::~Client() {}

void ClientManager::addClient(Client *user) {
    _clients[user->fd] = user;
}

void ClientManager::removeClient(int fd) {
    if (_clients.find(fd) != _clients.end()) {
        delete _clients[fd];
        _clients.erase(fd);
    }
}

void ClientManager::updateNickname(int fd, std::string nickname) {
  if (_clients.find(fd) != _clients.end())
    setNickname(fd, nickname);
}

// void ClientManager::printClient(int fd) const {
//   if (_clients.find(fd) == _clients.end()) {
//     std::cout << "Client with fd " << fd << " does not exist." << std::endl;
//     return;
//   }

//   const Client client = _clients.at(fd);
//   std::cout << "File Descriptor: " << client.fd << std::endl;
//   std::cout << "Nickname: " << client.nickname << std::endl;
//   std::cout << "Username: " << client.username << std::endl;
//   std::cout << "Hostname: " << client.hostname << std::endl;
//   std::cout << "Authenticated: " << (client.isAuthenticated ? "Yes" : "No")
//             << std::endl;
// }

// void ClientManager::printClients() const {
//   if (_clients.empty()) {
//     std::cout << "No clients connected." << std::endl;
//     return;
//   }

//   std::cout << "Connected Clients:" << std::endl;

//   for (std::map<int, Client*>::const_iterator it = _clients.begin();
//        it != _clients.end(); ++it) {
//     const Client client = it->second;
//     std::cout << "----------------------------------------" << std::endl;
//     printClient(client.fd);
//   }
//   std::cout << "----------------------------------------" << std::endl;
// }

//------------------getters------------------

Client *ClientManager::getClient(int fd) { return _clients[fd]; }

int ClientManager::getFd(std::string username) {
  std::map<int, Client*>::iterator it = _clients.begin();
  while (it != _clients.end()) {
    if (it->second->username == username)
      return it->first;
    it++;
  }
  return -1;
}

std::string ClientManager::getNickname(int fd) { return _clients[fd]->nickname; }

std::string ClientManager::getClientname(int fd) {
  return _clients[fd]->username;
}

std::string ClientManager::getHostname(int fd) { return _clients[fd]->hostname; }

const std::map<int, Client*> &ClientManager::getClients() const {
  return _clients;
}
// ------------------checkers------------------

bool ClientManager::usernameExists(std::string username) {
  std::map<int, Client*>::iterator it = _clients.begin();
  while (it != _clients.end()) {
    if (it->second->username == username)
      return true;
    it++;
  }
  return false;
}

bool ClientManager::nicknameExists(std::string nickname) {
  std::map<int, Client*>::iterator it = _clients.begin();
  while (it != _clients.end()) {
    if (it->second->nickname == nickname)
      return true;
    it++;
  }
  return false;
}

bool ClientManager::userExists(int fd) {
  return (_clients.find(fd) != _clients.end());
}

bool ClientManager::isAuthenticated(int fd) {
  return _clients[fd]->isAuthenticated;
}
// ------------------setters------------------
void ClientManager::setAuthenticated(int fd, bool isAuthenticated) {
  _clients[fd]->isAuthenticated = isAuthenticated;
}

void ClientManager::setNickname(int fd, std::string nickname) {
  _clients[fd]->nickname = nickname;
}

void ClientManager::setClientname(int fd, std::string username) {
  _clients[fd]->username = username;
}

void ClientManager::setHostname(int fd, std::string hostname) {
  _clients[fd]->hostname = hostname;
}

ClientManager::~ClientManager() {
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        delete it->second;
    }
    _clients.clear();
}
