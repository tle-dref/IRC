#include "validation.hpp"
#include <iostream>
#include <stdexcept>

void validateNick(ClientManager client, const TokenisedCommand& cmd) {
    if (cmd.getArguments().empty()) {
        throw std::runtime_error("431 :No nickname given");
    }
    const std::string& nickname = cmd.getArguments()[0];
    if (nickname.length() > 9 || !isalpha(nickname[0])) {
        throw std::runtime_error("432 :Erroneous nickname");
    }
	(void)client;
}

void validateUser(ClientManager client, const TokenisedCommand& cmd) { (void)client; (void)cmd; }
void validateJoin(ClientManager client, const TokenisedCommand& cmd) { (void)client; (void)cmd; }
void validatePrivMsg(ClientManager client, const TokenisedCommand& cmd) { (void)client; (void)cmd; }
void validateQuit(ClientManager client, const TokenisedCommand& cmd) { (void)client; (void)cmd; }
void validatePing(ClientManager client, const TokenisedCommand& cmd) { (void)client; (void)cmd; }
void validatePong(ClientManager client, const TokenisedCommand& cmd) { (void)client; (void)cmd; }