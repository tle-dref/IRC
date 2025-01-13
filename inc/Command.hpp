#pragma once
#include "Client.hpp"
#include "Tokenisation.hpp"
#include <string>
#include <vector>

class CommandList {
public:
  static const std::vector<std::string> &getCommands();
  static int findCommandIndex(const std::string &command);
};

void dispatchCommand(ClientManager client, const TokenisedCommand &cmd);
void handleInvalidCommand(ClientManager client, const std::string &command);

void validateNick(ClientManager client, const TokenisedCommand& cmd);
void validateUser(ClientManager client, const TokenisedCommand& cmd);
void validateJoin(ClientManager client, const TokenisedCommand& cmd);
void validatePrivMsg(ClientManager client, const TokenisedCommand& cmd);
void validateQuit(ClientManager client, const TokenisedCommand& cmd);
void validatePing(ClientManager client, const TokenisedCommand& cmd);
void validatePong(ClientManager client, const TokenisedCommand& cmd);
