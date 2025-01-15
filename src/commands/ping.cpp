#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validatePing(const TokenisedCommand &cmd, int fd) {
    if (cmd.getArguments().empty()) {
        std::string response = "409 :No origin specified\r\n";
        send(fd, response.c_str(), response.length(), 0);
        return false;
    }
    return true;
}

void Server::doPong(const TokenisedCommand &cmd, int fd) {
    std::string token = cmd.getArguments()[0];
    std::string response = "PONG :" + token + "\r\n";
    send(fd, response.c_str(), response.size(), 0);
    std::cout << "Send PONG response: " << response;
}
