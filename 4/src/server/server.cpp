#include "server.hpp"

Server::Server()
{
  NetTCPSocket::StartupSockets();
  server.StartServer();
  server.EnterLoop();
}

Server::~Server()
{
  NetTCPSocket::ShutdownSockets();
}