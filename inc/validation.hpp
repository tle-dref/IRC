#pragma once
#include "Tokenisation.hpp"
#include "ClientManager.hpp"

void validateNick(ClientManager client, const TokenisedCommand& cmd);
void validateUser(ClientManager client, const TokenisedCommand& cmd);
void validateJoin(ClientManager client, const TokenisedCommand& cmd);
void validatePrivMsg(ClientManager client, const TokenisedCommand& cmd);
void validateQuit(ClientManager client, const TokenisedCommand& cmd);
void validatePing(ClientManager client, const TokenisedCommand& cmd);
void validatePong(ClientManager client, const TokenisedCommand& cmd);
