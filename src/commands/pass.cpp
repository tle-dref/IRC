#include "Client.hpp"
#include "Tokenisation.hpp"
#include "Server.hpp"

bool Server::validatePass(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, const int idClient) {
  (void)clients;
  (void)channels;
  (void)cmd;
  (void)idClient;
  return true;
}

void Server::doPass(ClientManager& clients, ChannelManager& channels,
                  const TokenisedCommand &cmd, const int fdClient)
{
    (void)channels;
    if (cmd.getArguments()[0] == this->password)
        {
            clients.getClient(fdClient)->isAuthenticated = true;
            std::cout << "Mot de passe correct pour le client (fd: " << fdClient << ")" << std::endl;
        }
    else
        {
            std::string errorMsg = "ERROR :Mot de passe incorrect\r\n";
            send(fdClient, errorMsg.c_str(), errorMsg.size(), 0);
            close(fdClient );
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fdClient, NULL);
            delete _clients[fdClient];
            _clients.erase(fdClient);
            return;
        }
}
