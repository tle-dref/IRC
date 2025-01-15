#include "Tokenisation.hpp"
#include <sstream>
#include <stdexcept>

TokenisedCommand::TokenisedCommand() : _command("") {}

const std::string &TokenisedCommand::getCommand() const { return _command; }

const std::vector<std::string> &TokenisedCommand::getArguments() const {
  return _arguments;
}

void TokenisedCommand::setCommand(const std::string &command) {
  _command = command;
}

void TokenisedCommand::addArgument(const std::string &argument) {
  _arguments.push_back(argument);
}

void TokenisedCommand::print() const {
  std::cout << "Command: " << _command << std::endl;
  std::cout << "Arguments:";
  for (std::vector<std::string>::const_iterator it = _arguments.begin();
       it != _arguments.end(); ++it) {
    std::cout << " '" << *it << "'";
  }
  std::cout << std::endl;
}

bool TokenisedCommand::isValid() const { return !_command.empty(); }

TokenisedCommand tokenize(const std::string &rawCommand) {
  if (rawCommand.empty()) {
    throw std::invalid_argument("Empty command");
  }

  // Nettoyer la commande
  std::string cleanCommand = rawCommand;
  while (!cleanCommand.empty() && (cleanCommand[0] == '\r' || cleanCommand[0] == '\x04'))
    cleanCommand.erase(0, 1);
  while (!cleanCommand.empty() && (cleanCommand[cleanCommand.length()-1] == '\r' || cleanCommand[cleanCommand.length()-1] == '\x04'))
    cleanCommand.erase(cleanCommand.length()-1, 1);

  TokenisedCommand result;
  std::istringstream stream(cleanCommand);
  std::string token;

  // 1. Commande
  if (stream >> token) {
    result.setCommand(token);
  }

  // 2. Arguments
  while (stream >> token) {
    // Si on trouve un token qui commence par ':', on prend tout le reste de la ligne
    if (token[0] == ':') {
      std::string trailing;
      std::getline(stream, trailing);
      // On enlève le ':' et on ajoute le reste de la ligne
      result.addArgument(token.substr(1) + trailing);
      break;
    }
    // Sinon on ajoute juste le token
    result.addArgument(token);
  }

  return result;
}
