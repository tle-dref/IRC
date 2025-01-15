#include "Channel.hpp"
#include "Client.hpp"
#include <cassert>

void test_client_manager() {
  ClientManager manager;

  // Test adding client
  Client *client = new Client(42);
  manager.addClient(client);
  assert(manager.getClient(42) == client);

  // Test removing client
  manager.removeClient(42);
  assert(manager.getClient(42) == NULL);
}

void test_channel_manager() {
  ChannelManager manager;

  // Test adding channel
  Channel *channel = new Channel("#test");
  manager.addChannel("#test", channel);
  assert(manager.getChannel("#test") == channel);

  // Test removing channel
  manager.removeChannel("#test");
  assert(manager.getChannel("#test") == NULL);
}

int main() {
  test_client_manager();
  test_channel_manager();
  std::cout << "All memory tests passed!" << std::endl;
  return 0;
}
