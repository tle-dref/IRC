#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validateMode(const TokenisedCommand &cmd, int fd) {
	(void)cmd;
	(void)fd;
	return true;
}

void Server::doMode(const TokenisedCommand &cmd, int fd) {
	(void)cmd;
	(void)fd;
}