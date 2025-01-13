#pragma once
#include "Tokenisation.hpp"
#include "ClientManager.hpp"

void dispatchCommand(ClientManager client, const TokenisedCommand& cmd);
void handleInvalidCommand(ClientManager client, const std::string& command);
