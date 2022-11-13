#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include <netlib.hpp>
#include <protocol.hpp>

class ServerClient
{
  NetSocketType m_socket;
  std::string m_packet_buf{};
  protocol::Packets m_packet = protocol::PACKETS_SIZE;

public:
  ServerClient(NetSocketType socket)
    : m_socket(socket)
  { }

  std::string &GetPacketBuf()
  {
    return this->m_packet_buf;
  }

  NetSocketType GetSocket()
  {
    return this->m_socket;
  }

  void SetPacket(protocol::Packets packet)
  {
    this->m_packet = packet;
  }

  protocol::Packets GetPacket()
  {
    return this->m_packet;
  }

  void Handle()
  {
    switch (this->m_packet)
    {
    case protocol::PACKETS_SERVERBOUND_REQUEST_USERNAME:
      auto username = this->m_packet_buf.substr(0, 16);
      std::cout << "New username: " << username << std::endl;
    break;
    }

    // Clear the packet buf to signal we're done
    this->m_packet_buf.clear();
  }
};

struct ServerEvents
{
  Event<std::string_view, int> m_startup;
  Event<std::shared_ptr<ServerClient>> m_new_client;
};

template<ServerEvents Events> // Compile-time events structure
class Server
{
  std::string_view m_addr;
  int m_port;
  NetSocketType m_raw_socket;
  fd_set m_set;
  std::vector<std::shared_ptr<ServerClient>> m_clients{};

  void AcceptConnection(NetSocketType s)
  {
    // Accept the connection & set the fd_set accordingly
    auto client = netlib::Accept(this->m_raw_socket);
    FD_SET(client, &this->m_set);

    // Create new client wrapper and emplace to list of clients
    auto c = std::make_shared<ServerClient>(client);
    this->m_clients.emplace_back(c);

    // Call our event
    Events.m_new_client(c);
  }

  void HandleMessage(NetSocketType s)
  {
    // Find client if it exists
    auto pclient = std::find_if(this->m_clients.begin(), this->m_clients.end(), [&](auto c)
    {
      return c->GetSocket() == s;
    });

    // if not return
    if (pclient == this->m_clients.end())
      return;

    // If it does, dereference the iterator and grab the clients packet buffer
    auto client = *pclient;
    auto &packet_buf = client->GetPacketBuf();

    // Start of new message
    if (packet_buf.empty())
    {
      // Read the packet integer
      int packet_id;
      auto num = netlib::Read<int>(client->GetSocket(), &packet_id, sizeof packet_id);

      if (num <= 0)
        return; // TODO: Kill client

      // Set the currently client packet accordingly
      client->SetPacket(static_cast<protocol::Packets>(packet_id));
    }

    // Read a 4k buffer, if the message is fully enclosed within this buffer
    // we're done, otherwise we read another 4k on the next tick
    // until the message is fully digested

    constexpr auto buf_len = 4096;
    char buf[buf_len + 1]{0}; // +1 for null term
    auto x = netlib::Read<char>(client->GetSocket(), buf, buf_len);
    packet_buf.append(buf);

    if (strcmp(&buf[x - 2], "\r\r") != 0) // not fully digested
      return;

    // Handle the data
    client->Handle();
  }

  void RunSelect(fd_set &set_copy, int i)
  {
    if (!netlib::CheckIfSet(set_copy, i))
      return;

    auto s = netlib::GetSelectResult(set_copy, i);

    if (s == this->m_raw_socket)
      this->AcceptConnection(s);
    else
      this->HandleMessage(s);
  }

  void TickServer()
  {
    auto set_copy = this->m_set;
    auto res = netlib::SelectSocket(set_copy);

    if (res < 0)
      return;

    for (auto i = 0; i < res; i++)
    {
      this->RunSelect(set_copy, i);
    }
  }

public:
  Server(std::string_view addr, int port)
      : m_addr(addr), m_port(port)
  {
    netlib::StartupNetlib();

    this->m_raw_socket = netlib::CreateSocket();

    if (this->m_raw_socket == INVALID_SOCKET)
      return;

    if (!netlib::BindSocket(this->m_raw_socket, addr, port))
      return;

    if (!netlib::ListenSocket(this->m_raw_socket))
      return;

    FD_ZERO(&this->m_set);
    FD_SET(this->m_raw_socket, &this->m_set);

    Events.m_startup(addr, port);

    while (true)
    {
      //std::cout << "test" << std::endl;
      this->TickServer();
    }
  }

  Server(int port)
      : Server("0.0.0.0", port)
  { }

  ~Server()
  {
    netlib::CloseSocket(this->m_raw_socket);
    netlib::ShutdownNetlib();
  }
};

#endif