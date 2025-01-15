#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validatePart(const TokenisedCommand &cmd, int fd) {
    (void)cmd;
	(void)fd;
    return true;
}

void Server::doPart(const TokenisedCommand &cmd, int fd) {
	(void)cmd;
	(void)fd;
}