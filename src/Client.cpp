#include "Client.hpp"

Client::Client()
    : id(idGenerator()), fd(id), nickname(""), username(""), hostname(""),
      isOperator(false), isAuthenticated(false) {}

Client::Client(std::string nickname)
    : id(idGenerator()), nickname(nickname), username(""), hostname(""),
      isOperator(false), isAuthenticated(false) {}

Client::~Client() {}

int Client::idGenerator() {
  static int currentId = 0;
  return ++currentId;
}

void ClientManager::addClient(Client user) { _clients[user.id] = user; }

void ClientManager::removeClient(int id) { _clients.erase(id); }

void ClientManager::updateNickname(int id, std::string nickname) {
  if (_clients.find(id) != _clients.end())
    setNickname(id, nickname);
}

void ClientManager::printClient(int id) const {
  if (_clients.find(id) == _clients.end()) {
    std::cout << "Client with ID " << id << " does not exist." << std::endl;
    return;
  }

  const Client &client = _clients.at(id);
  std::cout << "Client ID: " << client.id << std::endl;
  std::cout << "File Descriptor: " << client.fd << std::endl;
  std::cout << "Nickname: " << client.nickname << std::endl;
  std::cout << "Username: " << client.username << std::endl;
  std::cout << "Hostname: " << client.hostname << std::endl;
  std::cout << "Operator: " << (client.isOperator ? "Yes" : "No") << std::endl;
  std::cout << "Authenticated: " << (client.isAuthenticated ? "Yes" : "No")
            << std::endl;
}

void ClientManager::printClients() const {
  if (_clients.empty()) {
    std::cout << "No clients connected." << std::endl;
    return;
  }

  std::cout << "Connected Clients:" << std::endl;

  for (std::map<int, Client>::const_iterator it = _clients.begin();
       it != _clients.end(); ++it) {
    const Client &client = it->second;
    std::cout << "----------------------------------------" << std::endl;
    printClient(client.id);
  }
  std::cout << "----------------------------------------" << std::endl;
}

//------------------getters------------------

Client *ClientManager::getClient(int id) { return &_clients[id]; }

int ClientManager::getFd(std::string username) {
  std::map<int, Client>::iterator it = _clients.begin();
  while (it != _clients.end()) {
    if (it->second.username == username)
      return it->first;
    it++;
  }
  return -1;
}

std::string ClientManager::getNickname(int id) { return _clients[id].nickname; }

std::string ClientManager::getClientname(int id) {
  return _clients[id].username;
}

std::string ClientManager::getHostname(int id) { return _clients[id].hostname; }

const std::map<int, Client> &ClientManager::getClients() const {
  return _clients;
}
// ------------------checkers------------------
bool ClientManager::isOperator(int id) { return _clients[id].isOperator; }

bool ClientManager::usernameExists(std::string username) {
  std::map<int, Client>::iterator it = _clients.begin();
  while (it != _clients.end()) {
    if (it->second.username == username)
      return true;
    it++;
  }
  return false;
}

bool ClientManager::nicknameExists(std::string nickname) {
  std::map<int, Client>::iterator it = _clients.begin();
  while (it != _clients.end()) {
    if (it->second.nickname == nickname)
      return true;
    it++;
  }
  return false;
}

bool ClientManager::userExists(int id) {
  return (_clients.find(id) != _clients.end());
}

bool ClientManager::isAuthenticated(int id) {
  return _clients[id].isAuthenticated;
}
// ------------------setters------------------
void ClientManager::setAuthenticated(int id, bool isAuthenticated) {
  _clients[id].isAuthenticated = isAuthenticated;
}

void ClientManager::setOperator(int id, bool isOperator) {
  _clients[id].isOperator = isOperator;
}

void ClientManager::setNickname(int id, std::string nickname) {
  _clients[id].nickname = nickname;
}

void ClientManager::setClientname(int id, std::string username) {
  _clients[id].username = username;
}

void ClientManager::setHostname(int id, std::string hostname) {
  _clients[id].hostname = hostname;
}