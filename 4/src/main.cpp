#include <iostream>

#include "server/server.hpp"

int main(int argc, char **argv)
{
  auto server = Server{};
  server.GetEvents()->m_startup = [](auto host, auto port) { std::cout << "Host: " << host << " Port: " << port; };

  return 0;
}