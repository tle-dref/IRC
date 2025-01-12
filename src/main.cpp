#include "Tokenisation.hpp"
#include <iostream>

int main() {
  std::string rawCommand = ":nick!user@host PRIVMSG #channel lol :Hello world!";

  try {
    TokenisedCommand cmd = tokenize(rawCommand);
    if (!cmd.isValid()) {
      std::cerr << "Invalid command received.\n";
      return 1;
    }
    cmd.print();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
