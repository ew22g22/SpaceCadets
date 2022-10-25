#ifndef SERVER_HPP
#define SERVER_HPP

#include "../net/net.hpp

class Server
{
  std::shared_ptr<NetServer> m_raw_server = nullptr;

public:
  Server();
  ~Server();
};

#endif