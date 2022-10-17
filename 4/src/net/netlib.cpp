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
}

NetTCPSocket::NetTCPSocket(std::string_view addr, int port)
{
  // Create the socket for AF_INET over TCP
  this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (!this->IsOpen())
    return;

  sockaddr_in hint{};
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port);
  inet_pton(this->m_socket, addr.data(), &hint.sin_addr);

  bind(this->m_socket, reinterpret_cast<sockaddr*>(&hint), sizeof hint);

  // TODO: Setup hint structure & bind socket 
}

NetTCPSocket::~NetTCPSocket() = default;

bool NetTCPSocket::IsOpen() const
{
  return this->m_socket != INVALID_SOCKET;
}