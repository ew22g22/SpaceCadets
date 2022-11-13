#include <iostream>

#include "server.hpp"

void StartupHandler(std::string_view addr, int port)
{
  std::cout << "[!] Server started." << std::endl;
}

void NewClientHandler(std::shared_ptr<ServerClient> client)
{
  std::cout << "[+] New client on socket " << client->GetSocket() << std::endl;
}

int main()
{
  /* Define event handlers */
  constexpr auto events = ServerEvents {
    .m_startup = StartupHandler,
    .m_new_client = NewClientHandler
  };

  /* Create server on given port */
  auto server = Server<events>{52000};
}