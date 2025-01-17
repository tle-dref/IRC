#pragma once
#include <iostream>
#include <string>
#include <vector>

class TokenisedCommand {
private:
  std::string _command;
  std::vector<std::string> _arguments;

public:
  TokenisedCommand();
  ~TokenisedCommand(){};

  const std::string &getCommand() const;
  const std::vector<std::string> &getArguments() const;

  void setCommand(const std::string &command);
  void addArgument(const std::string &argument);

  void print() const;
  bool isValid() const;
};

TokenisedCommand tokenize(const std::string &rawCommand);
