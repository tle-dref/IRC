#include "Channel.hpp"

Channel::Channel() : userLimit(-1), inviteOnly(false), topicRestricted(false) {}

Channel::Channel(std::string name)
    : name(name), userLimit(-1), inviteOnly(false), topicRestricted(false) {}

Channel::~Channel() {}

int Channel::getNbrUsersOn() { return users.size(); }

void ChannelManager::addChannel(std::string channelName, Channel channel) {
  _channels[channelName] = channel;
}

void ChannelManager::removeChannel(std::string channelName) {
  _channels.erase(channelName);
}

Channel *ChannelManager::getChannel(std::string channelName) {
  if (_channels.find(channelName) == _channels.end())
    return NULL;
  return &_channels[channelName];
}

void ChannelManager::addUser(std::string channelName, Client user) {
  if (_channels.find(channelName) == _channels.end()) // mesonge
    addChannel(channelName, Channel(channelName));
  if (isFull(channelName))
    return; // error a preciser throw out of bound
  _channels[channelName].users.insert(user.fd);
}

void ChannelManager::removeUser(std::string channelName, Client user) {
  if (isUserInChannel(
          channelName,
          user.fd)) // mesonge est ce que le user est dans le channel
    return;         // error a preciser
  _channels[channelName].users.erase(user.fd);
}

std::set<int> ChannelManager::getUsers(std::string channelName) {
  if (_channels.find(channelName) == _channels.end())
    return std::set<int>();
  return _channels[channelName].users;
}

std::set<int> ChannelManager::getOperators(std::string channelName) {
  if (_channels.find(channelName) == _channels.end())
    return std::set<int>();
  return _channels[channelName].operators;
}

int ChannelManager::getUserLimit(std::string channelName) {
  if (_channels.find(channelName) == _channels.end())
    return -1;
  return _channels[channelName].userLimit;
}

std::string ChannelManager::getPassword(std::string channelName) {
  if (_channels.find(channelName) == _channels.end())
    return "";
  return _channels[channelName].password;
}

const std::map<std::string, Channel> &ChannelManager::getChannels() const {
  return _channels;
}

void ChannelManager::setTopic(std::string channelName, std::string topic) {
  _channels[channelName].topic =
      topic; // in commande handler check op or topic for all
}

void ChannelManager::setUserLimit(std::string channelName, int userLimit) {
  _channels[channelName].userLimit =
      userLimit; // check if user is in the channel and is op
}

void ChannelManager::setPassword(std::string channelName,
                                 std::string password) {
  _channels[channelName].password =
      password; // check if user is in the channel and is op
}

void ChannelManager::setInviteOnly(std::string channelName, bool inviteOnly) {
  _channels[channelName].inviteOnly =
      inviteOnly; // check if user is in the channel and is op
}

void ChannelManager::setTopicRestricted(std::string channelName,
                                        bool topicRestricted) {
  _channels[channelName].topicRestricted =
      topicRestricted; // check if user is in the channel and is op
}

bool ChannelManager::channelExists(std::string channelName) {
  return (_channels.find(channelName) != _channels.end());
}

bool ChannelManager::userExists(std::string channelName, int fd) {
  return (_channels[channelName].users.find(fd) !=
          _channels[channelName].users.end());
}

bool ChannelManager::isOperator(std::string channelName, int fd) {
  return (_channels[channelName].operators.find(fd) !=
          _channels[channelName].operators.end());
}

bool ChannelManager::isInviteOnly(std::string channelName) {
  return _channels[channelName].inviteOnly;
}

bool ChannelManager::isTopicRestricted(std::string channelName) {
  return _channels[channelName].topicRestricted;
}

bool ChannelManager::isPasswordProtected(std::string channelName) {
  return !_channels[channelName].password.empty();
}

bool ChannelManager::isFull(std::string channelName) {
  return (_channels[channelName].userLimit != -1 &&
          _channels[channelName].users.size() >=
              (unsigned long long)_channels[channelName].userLimit);
}

bool ChannelManager::isUserInChannel(std::string channelName, int fd) {
  return (_channels[channelName].users.find(fd) !=
          _channels[channelName].users.end());
}

ChannelManager::ChannelManager() {}

ChannelManager::~ChannelManager() {}

// TESTS()
// {
//     Channel channel;
//     Client client("bob");

//     REQUIRE(channel.clients().length() == 0);
//     channel.addClient(client);
//     REQUIRE(channel.clients().length() == 1);
//     channel.removeClient(client);
//     REQUIRE(channel.clients().length() == 0);

//     Client client2("BOB");
//     CHECK_THROWS(channel.addClient(client2));
// }
