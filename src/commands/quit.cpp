#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validateQuit(const TokenisedCommand &cmd, int fd) {
    (void)cmd;
    (void)fd;
    return true;
}

void Server::doQuit(const TokenisedCommand &cmd, int fd) {
	(void)cmd;
	(void)fd;
}
