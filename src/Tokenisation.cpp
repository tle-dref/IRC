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
  std::cout << "Command: " << _command << "\n";
  std::cout << "Arguments: ";
  for (std::vector<std::string>::const_iterator it = _arguments.begin();
       it != _arguments.end(); ++it) {
    std::cout << "'" << *it << "' ";
  }
  std::cout << std::endl;
}

bool TokenisedCommand::isValid() const { return !_command.empty(); }

TokenisedCommand tokenize(const std::string &rawCommand) {
  if (rawCommand.empty()) {
    throw std::invalid_argument("Empty command");
  }

  TokenisedCommand result;
  std::istringstream stream(rawCommand);
  std::string token;

  // 1. Commande
  if (stream >> token) {
    result.setCommand(token);
  }

  // 3. Arguments
  while (stream >> token) {
    if (token[0] == ':') {
      std::string trailing;
      std::getline(stream, trailing);
      result.addArgument(token.substr(1) + trailing);
      break;
    } else {
      result.addArgument(token); // Ajoute le token classique
    }
  }

  return result;
}
