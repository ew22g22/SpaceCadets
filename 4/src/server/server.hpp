#ifndef SERVER_HPP
#define SERVER_HPP

#include "../net/net.hpp"

/* Wrapper class around NetServer for ease of use */
class Server
{
  std::shared_ptr<NetServer> m_raw_server = nullptr;    // Underlying NetServer instance

public:
  Server();
  ~Server();

  std::shared_ptr<NetServerEvents> GetEvents() const;   // Return the NetServerEvents structure from the NetServer instance
};

#endif