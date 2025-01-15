// kick.cpp

#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Tokenisation.hpp"
#include <iostream>
#include <map>

bool Server::validateKick(const TokenisedCommand &cmd, int fd) {
    if (cmd.getArguments().size() < 2) {
        std::string response = "461 KICK :Not enough parameters\r\n";
        send(fd, response.c_str(), response.length(), 0);
        return false;
    }

    const std::string &channel = cmd.getArguments()[0];
    const std::string &target = cmd.getArguments()[1];
    
    // Vérifier si le canal existe
    if (!_channels.channelExists(channel)) {
        std::string response = "403 " + channel + " :No such channel\r\n";
        send(fd, response.c_str(), response.length(), 0);
        return false;
    }
    
    // Vérifier si l'utilisateur est opérateur du canal
    if (!_channels.isOperator(channel, fd)) {
        std::string response = "482 " + channel + " :You're not channel operator\r\n";
        send(fd, response.c_str(), response.length(), 0);
        return false;
    }
    
    // Vérifier si la cible existe dans le canal
    int targetFd = _clients.getFd(target);
    if (targetFd == -1 || !_channels.isUserInChannel(channel, targetFd)) {
        std::string response = "441 " + target + " " + channel + " :They aren't on that channel\r\n";
        send(fd, response.c_str(), response.length(), 0);
        return false;
    }
    
    return true;
}

void Server::doKick(const TokenisedCommand &cmd, int fd) {
    (void)cmd;
    (void)fd;
}
