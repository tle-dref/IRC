#include "Channel.hpp"      // Pour Channel, ChannelManager
#include "Client.hpp"       // Pour Client, ClientManager
#include "Command.hpp"      // Pour dispatchCommand(...)
#include "Tokenisation.hpp" // Pour tokenize(...)
#include <iostream>
#include <string>

// int main() {
//   // 1) Initialiser vos objets (ClientManager, ChannelManager, etc.)
//   // ----------------------------------------------------------------
//   std::string channelName = "#myChannel";

//   ClientManager clients;
//   Channel myChannel(channelName);
//   ChannelManager channels;

//   Client client1;
//   Client client2;
//   client1.nickname = "myNickname";
//   client1.username = "myUsername";
//   client1.hostname = "myHostname";

//   client2.nickname = "jack";

//   // Ajouter clients dans le ClientManager
//   clients.addClient(client1);
//   clients.addClient(client2);

//   // Ajouter channel dans le ChannelManager
//   channels.addChannel(channelName, myChannel);

//   // Limite, password
//   channels.setUserLimit(channelName, 2);
//   channels.setPassword(channelName, "ptdr");

//   // Ajouter des utilisateurs au channel
//   channels.addUser(channelName, &client1);
//   channels.addUser(channelName, &client2);

//   // 2) Boucle de lecture des commandes
//   // ----------------------------------------------------------------
//   while (true) {
//     std::string rawCommand;
//     std::cout << "ircGolem> ";
//     if (!std::getline(std::cin, rawCommand)) {
//       // Si on arrive ici, c'est probablement un EOF (Ctrl+D)
//       std::cout << "Fin de l'entrée standard. Fermeture du programme."
//                 << std::endl;
//       break;
//     }

//     // Si l'utilisateur veut quitter le programme
//     if (rawCommand == "EXIT" || rawCommand == "QUIT") {
//       std::cout << "Fermeture du programme sur commande utilisateur."
//                 << std::endl;
//       break;
//     }

//     // 3) Tokenizer et valider la commande
//     // ----------------------------------------------------------------
//     TokenisedCommand cmd = tokenize(rawCommand);
//     if (!cmd.isValid()) {
//       std::cerr << "Invalid command received." << std::endl;
//       continue; // On passe à l'itération suivante
//     }

//     // 4) Dispatcher la commande
//     //    (Dans votre logique, vous devrez peut-être identifier
//     //     quel client FD/ID exécute la commande. Ici, on utilise
//     //     l'ID de client1 comme exemple.)
//     // ----------------------------------------------------------------
//     dispatchCommand(clients, channels, cmd, client1.id);

//     // 5) (Optionnel) Vous pouvez afficher les clients, channels, etc.
//     // ----------------------------------------------------------------
//     clients.printClients();
//   }

//   return 0;
// }


#include "Server.hpp"
#include <cstdlib>
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return (1);
	}
	int port = std::atoi(argv[1]);
	std::string password = argv[2];
	ClientManager clients;
	ChannelManager channels;
	
	Server server(port, password, clients, channels);
	server.run();
	return (0);
}