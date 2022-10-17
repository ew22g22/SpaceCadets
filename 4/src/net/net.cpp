#include "net.hpp"
#include "netlib.hpp"

// Explicitly instantiate required template arguments
// needed for NetServer and NetClient
template class NetBase<NetServerEvents>;
template class NetBase<NetClientEvents>;

int NetBase::SetErrorCode(int current, int code)
{
  return (current | code);
}

int NetBase::UnsetErrorCode(int current, int code)
{
  return (current & ~code);
}

template<typename EventsType>
NetBase<EventsType>::NetBase(std::string_view addr, int port)
    : m_addr(addr), m_port(port)
{
  this->m_events = std::make_shared<EventsType>();
}

template<typename EventsType>
NetBase<EventsType>::~NetBase() = default;

template<typename EventsType>
std::string_view NetBase<EventsType>::GetAddress() const
{
  return this->m_addr;
}

template<typename EventsType>
int NetBase<EventsType>::GetPort() const
{
  return this->m_port;
}

NetServer::NetServer(int port)
    : NetBase("0.0.0.0", port)
{
  // Initialize the events structure
  this->m_events = std::make_shared<NetServerEvents>();
}

NetServer::~NetServer() = default;

int NetServer::StartServer()
{
  auto result = 0;
  auto socket = NetTCPSocket{};

  if (!socket.IsOpen())
    return NetBase::SetErrorCode(result, NET_ERROR_INVALID_SOCKET);

  
}

std::shared_ptr<NetServerEvents> NetServer::GetEvents() const
{
  return this->m_events;
}

void NetServer::StopServer()
{

}

NetClient::NetClient(std::string_view addr, int port)
    : NetBase(addr, port)
{ }

NetClient::~NetClient() = default;