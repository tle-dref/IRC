#pragma once
#include "Client.hpp"
#include <iostream>
#include <map>
#include <set>

struct Client;

struct Channel {
  std::string name;        // Nom du channel
  std::string topic;       // Sujet du channel
  std::set<int> users;     // Liste des utilisateurs par FD
  std::set<int> operators; // Liste des opérateurs par FD
  int userLimit;           // Limite d'utilisateurs
  std::string password;    // Mot de passe du channel
  bool inviteOnly;         // Mode sur invitation
  bool topicRestricted;    // Restriction de modification du topic
  Channel();
  Channel(std::string name);
  ~Channel();
  int getNbrUsersOn();
  void notifyChannel(std::string message); // TODO
};

class ChannelManager {
private:
  std::map<std::string, Channel> _channels;

public:
  ChannelManager();
  ~ChannelManager();

  // functions
  void addChannel(std::string channelName, Channel channel);
  void removeChannel(std::string channelName);
  void addUser(std::string channelName, Client user);
  void removeUser(std::string channelName, Client user);

  // getter
  Channel *getChannel(std::string channelName);
  std::set<int> getUsers(std::string channelName);
  std::set<int> getOperators(std::string channelName);
  int getUserLimit(std::string channelName);
  std::string getPassword(std::string channelName);
  const std::map<std::string, Channel> &getChannels() const;

  // setter
  void setTopic(std::string channelName, std::string topic);
  void setUserLimit(std::string channelName, int userLimit);
  void setPassword(std::string channelName, std::string password);
  void setInviteOnly(std::string channelName, bool inviteOnly);
  void setTopicRestricted(std::string channelName, bool topicRestricted);

  // check
  bool channelExists(std::string channelName);
  bool userExists(std::string channelName, int fd);
  bool isOperator(std::string channelName, int fd);
  bool isInviteOnly(std::string channelName);
  bool isTopicRestricted(std::string channelName);
  bool isPasswordProtected(std::string channelName);
  bool isFull(std::string channelName);
  bool isUserInChannel(std::string channelName, int fd);
};