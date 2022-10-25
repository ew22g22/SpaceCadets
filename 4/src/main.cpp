#include <iostream>

#include "net/net.hpp"
#include "net/netlib.hpp"

int main(int argc, char **argv)
{
  auto server = NetServer{52000};
  server.GetEvents()->m_startup = [](auto host, auto port) { std::cout << "Host: " << host << " Port: " << port; };

  NetTCPSocket::StartupSockets();
  server.StartServer();
  server.EnterLoop();

  NetTCPSocket::ShutdownSockets();

  return 0;
}