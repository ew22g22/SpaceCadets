#include "server.hpp"
#include "../net/netlib.hpp"

Server::Server()
{
  // Start up WinSock if on windows
  NetTCPSocket::StartupSockets();

  // Initialize NetServer instance
  this->m_raw_server = std::make_shared<NetServer>(52000);

  // Start the server and enter the loop on a different thread
  // (leave main thread open for commands)
  this->m_raw_server->StartServer();
  this->m_raw_server->EnterLoop();
}

Server::~Server()
{
  // Shut down WinSock if on windows
  NetTCPSocket::ShutdownSockets();
}

std::shared_ptr<NetServerEvents> Server::GetEvents() const
{
  return this->m_raw_server->GetEvents();
}