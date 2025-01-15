#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_NAME "GLMRC"

void error_443(int fd, std::string client, std::string channel);
void error_441(int fd, std::string client, std::string channel);
void error_476(int fd, std::string client, std::string channel);
void error_403(int fd, std::string client, std::string channel);
void error_442(int fd, std::string client, std::string channel);
void error_461(int fd, std::string client, std::string command);
void error_482(int fd, std::string client, std::string channel);
void error_501(int fd, std::string client);
void error_431(int fd, std::string client);
void error_432(int fd, std::string client, std::string target_nick);
void error_433(int fd, std::string client, std::string target_nick);
void error_436(int fd, std::string client, std::string target_nick);
void error_401(int fd, std::string client, std::string target_nick);
void error_402(int fd, std::string client, std::string target_server);
void error_404(int fd, std::string client, std::string channel);
void error_411(int fd, std::string client);
void error_412(int fd, std::string client);
void error_462(int fd, std::string client);
void error_405(int fd, std::string client, std::string channel);
void error_406(int fd, std::string client, std::string target_nick);
void error_409(int fd, std::string client);
void error_417(int fd, std::string client);
void error_421(int fd, std::string client);
void error_451(int fd, std::string client);
void error_464(int fd, std::string client);
void error_465(int fd, std::string client);
void error_471(int fd, std::string client, std::string channel);
void error_472(int fd, std::string client, std::string mode_char);
void error_473(int fd, std::string client, std::string channel);
void error_474(int fd, std::string client, std::string channel);
void error_475(int fd, std::string client, std::string channel);
void error_483(int fd, std::string client);
void error_491(int fd, std::string client);
