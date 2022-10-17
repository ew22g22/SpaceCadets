#include <iostream>

#include "net/net.hpp"

int main(int argc, char **argv)
{
  auto server = NetServer{52000};
  server.GetEvents()->m_startup = [](auto host, auto port) { std::cout << "Host: " << host << " Port: " << port; };

  server.StartServer();

  server.StopServer();

  return 0;
}