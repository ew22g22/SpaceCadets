#include "netlib.hpp"

NetTCPSocket::NetTCPSocket()
{
  // Create the socket for AF_INET over TCP
  this->m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // TODO: Setup hint structure & bind socket 
}

NetTCPSocket::~NetTCPSocket() = default;

bool NetTCPSocket::IsOpen() const
{
  return this->m_socket;
}