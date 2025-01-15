#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validatePrivmsg(const TokenisedCommand &cmd, int fd) {
    if (cmd.getArguments().size() < 2) {
        std::string response = "461 PRIVMSG :Not enough parameters\r\n";
        send(fd, response.c_str(), response.length(), 0);
        return false;
    }
    return true;
}

void Server::doPrivmsg(const TokenisedCommand &cmd, int fd) {
    std::string channelName = cmd.getArguments()[0];
    std::string message = ":" + _clients.getClient(fd)->nickname + " PRIVMSG " + channelName + " :" + cmd.getArguments()[1] + "\n";
    //std::string msg = ":" + clients.getClient(fdClient)->nickname + " " + cmd.getArguments()[1];
  //  std::cout << "message : " << msg << std::endl;
    //std::cout << "channelName : " << channelName << std::endl;
    _channels.msgChannel(message, channelName, fd);
}
