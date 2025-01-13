#include "commandHandler.hpp"
#include "ClientManager.hpp"
#include "CommandList.hpp"
#include "validation.hpp"
#include <iostream>
#include <sys/socket.h>

void dispatchCommand(ClientManager client, const TokenisedCommand &cmd) {
  int commandIndex = CommandList::findCommandIndex(cmd.getCommand());

  switch (commandIndex) {
  case 0: // NICK
    validateNick(client, cmd);
    // doNick();
    break;

  case 1: // USER
    validateUser(client, cmd);
    // doUser();
    break;

  case 2: // JOIN
    validateJoin(client, cmd);
    // doJoin();
    break;

  case 3: // PRIVMSG
    validatePrivMsg(client, cmd);
    // doPrivMsg();
    break;

  case 4: // QUIT
    validateQuit(client, cmd);
    // doQuit();
    break;

  case 5: // PING
    validatePing(client, cmd);
    // doPing();
    break;

  case 6: // PONG
    validatePong(client, cmd);
    // doPong();
    break;

  default:
    handleInvalidCommand(client, cmd.getCommand());
    break;
  }
}

void handleInvalidCommand(ClientManager client, const std::string &command) {
  throw std::runtime_error("error_421");
  (void)client;
  (void)command;
}
