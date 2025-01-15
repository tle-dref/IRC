#pragma once
# include "Client.hpp"
# include <iostream>
# include <map>
# include <set>
# include <arpa/inet.h>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <fcntl.h>
# include <iomanip>
# include <iostream>
# include <netinet/in.h>
# include <sys/epoll.h>
# include <unistd.h>
# include <map>
# include <sstream>
# include <sys/socket.h>

struct Client;

struct Channel {
  std::string name;        // Nom du channel
  std::string topic;       // Sujet du channel
  std::set<int> users;     // Liste des utilisateurs par fd
  std::set<int> operators; // Liste des opérateurs par fd
  std::set<int> banned;    // List des bans par fd
  int userLimit;           // Limite d'utilisateurs
  std::string password;    // Mot de passe du channel
  bool inviteOnly;         // Mode sur invitation
  bool topicRestricted;    // Restriction de modification du topic
  Channel();
  Channel(std::string name);
  ~Channel();
};

class ChannelManager {
private:
  std::map<std::string, Channel*> _channels;

public:
  ChannelManager();
  ~ChannelManager();

  // functions
  void msgChannel(std::string message, std::string channelName, int fd);
  void addChannel(std::string channelName, Channel *channel);
  void removeChannel(std::string channelName);
  void addUser(std::string channelName, Client *user);
  void removeUser(std::string channelName, Client user);
  void banUser(const std::string &chanName, int fd);
  void unbanUser(const std::string &chanName, int fd);
  void addOperator(std::string channelName, Client *user);
  void notifyChannel(std::string message, std::string chanName);

  // getter
  int getNbrUsersOn(const std::string &channelName);
  Channel *getChannel(std::string channelName);
  std::set<int> getUsers(std::string channelName);
  std::set<int> getOperators(std::string channelName);
  int getUserLimit(std::string channelName);
  std::string getPassword(std::string channelName);
  const std::map<std::string, Channel*> &getChannels() const;
  void getBannedUser(const std::string &chanName);

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
  bool isBanned(const std::string &channelName, int fd);
};
