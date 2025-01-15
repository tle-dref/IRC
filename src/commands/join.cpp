#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Tokenisation.hpp"

bool Server::validateJoin(const TokenisedCommand &cmd, int fd) {
    if (cmd.getArguments().empty()) {
        std::string response = "461 JOIN :Not enough parameters\r\n";
        send(fd, response.c_str(), response.length(), 0);
        return false;
    }

	std::string channelName = cmd.getArguments()[0];
    if (_channels.getChannel(channelName) == NULL) {
      _channels.addChannel(channelName, new Channel(channelName));
      _channels.addOperator(channelName, _clients.getClient(fd));
    }
    _channels.addUser(channelName, _clients.getClient(fd));

    std::set<int> users = _channels.getUsers(channelName);
    std::set<int>::iterator it = users.begin();
    while (it != users.end()) {
      std::cout << "user : " << *it << " is in " << channelName << std::endl;
      it++;
    }
    return true;
}

void Server::doJoin(const TokenisedCommand &cmd, int fd) {
    const std::string &channelName = cmd.getArguments()[0];
    
    // Vérifier si le canal existe, sinon le créer
    if (!_channels.channelExists(channelName)) {
        _channels.addChannel(channelName, new Channel(channelName));
        _channels.addOperator(channelName, _clients.getClient(fd));
    }
    
    // Ajouter l'utilisateur au canal
    _channels.addUser(channelName, _clients.getClient(fd));
    
    // Envoyer la confirmation
    std::string joinMsg = ":" + _clients.getClient(fd)->nickname + " JOIN " + channelName + "\r\n";
    _channels.notifyChannel(joinMsg, channelName);
}
