#pragma once
#include "Client.hpp"
#include "Tokenisation.hpp"
#include <string>
#include <vector>

class CommandList {
public:
  static const std::vector<std::string> &getCommands();
  static int findCommandIndex(const std::string &cmd);
};

void dispatchCommand(ClientManager clients, const TokenisedCommand &cmd);
void handleInvalidCommand(ClientManager clients, const std::string &cmd);

void validateNick(ClientManager clients, const TokenisedCommand& cmd);
void validateUser(ClientManager clients, const TokenisedCommand& cmd);
void validateJoin(ClientManager clients, const TokenisedCommand& cmd);
void validatePrivMsg(ClientManager clients, const TokenisedCommand& cmd);
void validateQuit(ClientManager clients, const TokenisedCommand& cmd);
void validatePing(ClientManager clients, const TokenisedCommand& cmd);
void validatePong(ClientManager clients, const TokenisedCommand& cmd);
