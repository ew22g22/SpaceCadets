#include "netlib.hpp"

static void NetTCPSocket::StartupSockets()
{
#ifdef WIN32
  WSADATA data{};
  auto ver = MAKEWORD(2, 2);
  WSAStartup(ver, &data);
#endif
}

static void NetTCPSocket::ShutdownSockets()
{
#ifdef WIN32
  WSACleanup();
#endif
}

NetTCPSocket::NetTCPSocket(std::string_view addr, int port)
{
  // Create the socket for AF_INET over TCP
  this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // If we failed to open, return
  if (!this->IsOpen())
    return;

  // Setup hint structure
  sockaddr_in hint{};
  hint.sin_family = AF_INET;                                // AF_INET
  hint.sin_port = htons(port);                              // Set port
  inet_pton(this->m_socket, addr.data(), &hint.sin_addr);   // Set host/address

  // Bind to socket
  if (bind(this->m_socket, reinterpret_cast<sockaddr*>(&hint), sizeof hint) != 0)
    return;

  this->m_bound = true;

  // Listen on socket
  if (listen(this->m_socket, SOMAXCONN) != 0)
    return;

  this->m_listening = true;

  // Clear the FD_SET and set the listening socket
  FD_ZERO(&this->m_set);
  FD_SET(this->m_listening, &this->m_set);
}

NetTCPSocket::~NetTCPSocket()
{
  socketclose(this->m_socket);
}

bool NetTCPSocket::IsOpen() const
{
  return this->m_socket != INVALID_SOCKET;
}

bool NetTCPSocket::IsBound() const
{
  return this->m_bound;
}

bool NetTCPSocket::IsListening() const
{
  return this->m_listening;
}