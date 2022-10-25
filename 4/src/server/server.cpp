#include "server.hpp"
#include "../net/netlib.hpp"

Server::Server()
{
  NetTCPSocket::StartupSockets();

  this->m_raw_server = std::make_shared<NetServer>(52000);

  this->m_raw_server->StartServer();
  this->m_raw_server->EnterLoop();
}

Server::~Server()
{
  NetTCPSocket::ShutdownSockets();
}

std::shared_ptr<NetServerEvents> Server::GetEvents() const
{
  return this->m_raw_server->GetEvents();
}