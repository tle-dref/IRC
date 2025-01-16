#include "Errors.hpp"

// DEBUGGAGE
// Simuler la fonction send pour tester
// ssize_t send(int fd, const char* buf, size_t len, int flags) {
// 	std::cout << "Sending message to fd " << fd << ": " << std::string(buf,
// len) << std::endl; 	std::cout << "Message length: " << len << std::endl;
// 	return len;  // Simuler l'envoi avec succès
// }

// void error_443(int fd, std::string client, std::string channel);
void error_443(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 443 " + client +
                         std::string(" ") + channel +
                         " :is already on channel" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "443 ERR_USERONCHANNEL" << std::endl;
  return;
}

// void error_441(int fd, std::string client, std::string channel);
void error_441(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 441 " + client +
                         std::string(" ") + channel +
                         " :They aren't on that channel" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "fd = " << fd << std::endl;
  std::cout << "client = " << client << std::endl;
  std::cout << "channel = " << channel << std::endl;
  std::cout << "441 ERR_USERNOTINCHANNEL" << std::endl;
  return;
}

// void error_476(int fd, std::string client, std::string channel);
void error_476(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 476 " + client +
                         std::string(" ") + channel + " :Bad Channel Mask" +
                         "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "476 ERR_BADCHANMASK" << std::endl;
  return;
}

// void error_403(int fd, std::string client, std::string channel);
void error_403(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 403 " + client +
                         std::string(" ") + channel + " :No such channel" +
                         "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "403 ERR_NOSUCHCHANNEL" << std::endl;
  return;
}

// void error_442(int fd, std::string client, std::string channel);
void error_442(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 442 " + client +
                         std::string(" ") + channel +
                         " :You're not on that channel" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "442 ERR_NOTONCHANNEL" << std::endl;
  return;
}

// void error_461(int fd, std::string client, std::string command);
void error_461(int fd, std::string client, std::string command) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 461 " + client +
                         command + " :Not enough parameters" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "461 ERR_NEEDMOREPARAMS" << std::endl;
  return;
}

// void error_482(int fd, std::string client, std::string channel);
void error_482(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 482 " + client +
                         std::string(" ") + channel +
                         " :You're not channel operator" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "482 ERR_CHANOPRIVSNEEDED" << std::endl;
  return;
}

// void error_501(int fd, std::string client);
void error_501(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 501 " + client +
                         " :Unknown MODE flag" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "501 ERR_UMODEUNKNOWNFLAG" << std::endl;
  return;
}

// void error_431(int fd, std::string client);
void error_431(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 431 " + client +
                         " :No nickname given" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "431 ERR_NONICKNAMEGIVEN" << std::endl;
  return;
}

// void error_432(int fd, std::string client, std::string target_nick);
void error_432(int fd, std::string client, std::string target_nick) {
  // if (client == nullptr || !client->isConnected())
  // 	return;
  (void)target_nick;
  std::string errorMsg = std::string(":") + SERVER_NAME + " 432 " + client +
                         " :" + target_nick +
                         ": nickname too long"
                         "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "432 ERR_ERRONEUSNICKNAME" << std::endl;
  return;
}

// void error_433(int fd, std::string client, std::string target_nick);
void error_433(int fd, std::string client, std::string target_nick) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 433 " + client +
                         " :" + target_nick + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "433 ERR_NICKNAMEINUSE" << std::endl;
  return;
}

// void error_436(int fd, std::string client, std::string target_nick);
void error_436(int fd, std::string client, std::string target_nick) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 436 " + client +
                         target_nick +
                         ":Nickname collision KILL from <user>@<host>" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "436 ERR_NICKCOLLISION" << std::endl;
  return;
}

// void error_401(int fd, std::string client, std::string target_nick);
void error_401(int fd, std::string client, std::string target_nick) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 401 " + client +
                         target_nick + " :No such nick/channel" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "401 ERR_NOSUCHNICK" << std::endl;
  return;
}

// void error_402(int fd, std::string client, std::string target_server);
void error_402(int fd, std::string client, std::string target_server) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 402 " + client +
                         target_server + " :No such server" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "402 ERR_NOSUCHSERVER" << std::endl;
  return;
}

// void error_404(int fd, std::string client, std::string channel);
void error_404(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 404 " + client +
                         std::string(" ") + channel +
                         " :Cannot send to channel" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "404 ERR_CANNOTSENDTOCHAN" << std::endl;
  return;
}

// void error_411(int fd, std::string client);
void error_411(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 411 " + client +
                         " :No recipient given (<command>)" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "411 ERR_NORECIPIENT" << std::endl;
  return;
}

// void error_412(int fd, std::string client);
void error_412(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 412 " + client +
                         " :No text to send" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "412 ERR_NOTEXTTOSEND" << std::endl;
  return;
}

// void error_462(int fd, std::string client);
void error_462(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 462 " + client +
                         " :You may not reregister" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "462 ERR_ALREADYREGISTERED" << std::endl;
  return;
}

// void error_405(int fd, std::string client, std::string channel);
void error_405(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 405 " + client +
                         std::string(" ") + channel +
                         " :You have joined too many channels" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "405 ERR_TOOMANYCHANNELS" << std::endl;
  return;
}

// void error_406(int fd, std::string client, std::string target_nick);
void error_406(int fd, std::string client, std::string target_nick) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 406 " + client +
                         target_nick + " :There was no such nickname" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "406 ERR_WASNOSUCHNICK" << std::endl;
  return;
}

// void error_409(int fd, std::string client);
void error_409(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 409 " + client +
                         " :No origin specified" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "409 ERR_NOORIGIN" << std::endl;
  return;
}

// void error_417(int fd, std::string client);
void error_417(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 417 " + client +
                         " :Input line was too long" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "417 ERR_INPUTTOOLONG" << std::endl;
  return;
}

// void error_421(int fd, std::string client);
void error_421(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 421 " + client +
                         " <command> :Unknown command" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "421 ERR_UNKNOWNCOMMAND" << std::endl;
  return;
}

// void error_451(int fd, std::string client);
void error_451(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 451 " + client +
                         " :You have not registered" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "451 ERR_NOTREGISTERED" << std::endl;
  return;
}

// void error_464(int fd, std::string client);
void error_464(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 464 " + client +
                         " :Password incorrect" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "464 ERR_PASSWDMISMATCH" << std::endl;
  return;
}

// void error_465(int fd, std::string client);
void error_465(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 465 " + client +
                         " :You are banned from this server." + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "465 ERR_YOUREBANNEDCREEP" << std::endl;
  return;
}

// void error_471(int fd, std::string client, std::string channel);
void error_471(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 471 " + client +
                         std::string(" ") + channel +
                         " :Cannot join channel (+l)" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "471 ERR_CHANNELISFULL" << std::endl;
  return;
}

// void error_472(int fd, std::string client, std::string mode_char);
void error_472(int fd, std::string client, char mode_char) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 472 " + client +
                         mode_char + " :is unknown mode char to me" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "472 ERR_UNKNOWNMODE" << std::endl;
  return;
}

// void error_473(int fd, std::string client, std::string channel);
void error_473(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 473 " + client +
                         std::string(" ") + channel +
                         " :Cannot join channel (+i)" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "473 ERR_INVITEONLYCHAN" << std::endl;
  return;
}

// void error_474(int fd, std::string client, std::string channel);
void error_474(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 474 " + client +
                         std::string(" ") + channel +
                         " :Cannot join channel (+b)" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "474 ERR_BANNEDFROMCHAN" << std::endl;
  return;
}

// void error_475(int fd, std::string client, std::string channel);
void error_475(int fd, std::string client, std::string channel) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 475 " + client +
                         std::string(" ") + channel +
                         " :Cannot join channel (+k)" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "475 ERR_BADCHANNELKEY" << std::endl;
  return;
}

// void error_483(int fd, std::string client);
void error_483(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 483 " + client +
                         " :You cant kill a server!" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "483 ERR_CANTKILLSERVER" << std::endl;
  return;
}

// void error_491(int fd, std::string client);
void error_491(int fd, std::string client) {
  // if (client == nullptr || !client->isConnected())
  // 	return;

  std::string errorMsg = std::string(":") + SERVER_NAME + " 491 " + client +
                         " :No O-lines for your host" + "\n";
  send(fd, errorMsg.c_str(), errorMsg.size(), MSG_NOSIGNAL);
  std::cout << "491 ERR_NOOPERHOST" << std::endl;
  return;
}
