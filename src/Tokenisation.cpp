#include "Tokenisation.hpp"
#include <sstream>
#include <stdexcept>

TokenisedCommand::TokenisedCommand()
    : _prefix(""), _command(""), _trailing("") {}

const std::string &TokenisedCommand::getPrefix() const { return _prefix; }

const std::string &TokenisedCommand::getCommand() const { return _command; }

const std::vector<std::string> &TokenisedCommand::getArguments() const {
  return _arguments;
}

const std::string &TokenisedCommand::getTrailing() const { return _trailing; }

void TokenisedCommand::setPrefix(const std::string &prefix) {
  _prefix = prefix;
}

void TokenisedCommand::setCommand(const std::string &command) {
  _command = command;
}

void TokenisedCommand::addArgument(const std::string &argument) {
  _arguments.push_back(argument);
}

void TokenisedCommand::setTrailing(const std::string &trailing) {
  _trailing = trailing;
}

void TokenisedCommand::print() const {
  std::cout << "Prefix: " << _prefix << "\n";
  std::cout << "Command: " << _command << "\n";
  std::cout << "Arguments: ";
  for (std::vector<std::string>::const_iterator it = _arguments.begin();
       it != _arguments.end(); ++it) {
    std::cout << "'" << *it << "' ";
  }
  std::cout << "\nTrailing: " << _trailing << "\n";
}

bool TokenisedCommand::isValid() const { return !_command.empty(); }

TokenisedCommand tokenize(const std::string &rawCommand) {
  if (rawCommand.empty()) {
    throw std::invalid_argument("Empty command");
  }

  TokenisedCommand result;
  std::istringstream stream(rawCommand);
  std::string token;

  // 1. Préfixe
  if (rawCommand[0] == ':') {
    stream >> token;
    result.setPrefix(token.substr(1));
  }

  // 2. Commande
  if (stream >> token) {
    result.setCommand(token);
  }

  // 3. Arguments et trailing
  while (stream >> token) {
    if (token[0] == ':') {
      std::getline(stream, token);
      result.setTrailing(token.substr(1));
      break;
    } else {
      result.addArgument(token);
    }
  }

  return result;
}
