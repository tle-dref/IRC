#pragma once
#include <iostream>
#include <string>
#include <vector>

class TokenisedCommand {
private:
    std::string _prefix;
    std::string _command;
    std::vector<std::string> _arguments;
    std::string _trailing;

public:
    TokenisedCommand();

    const std::string& getPrefix() const;
    const std::string& getCommand() const;
    const std::vector<std::string>& getArguments() const;
    const std::string& getTrailing() const;

    void setPrefix(const std::string& prefix);
    void setCommand(const std::string& command);
    void addArgument(const std::string& argument);
    void setTrailing(const std::string& trailing);

    void print() const;
    bool isValid() const;
};

TokenisedCommand tokenize(const std::string& rawCommand);
