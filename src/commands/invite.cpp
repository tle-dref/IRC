#include "Server.hpp"

bool validateInvite(const TokenisedCommand &cmd, int fd) {
  (void)cmd;
  (void)fd;
  return true;
}
void doInvite(const TokenisedCommand &cmd, int fd) {
  (void)cmd;
  (void)fd;
}