#include "net.hpp"
#include "netlib.hpp"
#include "action.hpp"

// Explicitly instantiate required template arguments
// needed for NetServer and NetClient
template class NetBase<NetServerEvents>;
template class NetBase<NetClientEvents>;

template<typename EventsType>
int NetBase<EventsType>::SetErrorCode(int current, int code)
{
  return (current | code);
}

template<typename EventsType>
int NetBase<EventsType>::UnsetErrorCode(int current, int code)
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

}

NetServer::~NetServer() = default;

int NetServer::StartServer()
{
  auto result = 0;
  auto socket = NetTCPSocket{this->m_addr, this->m_port};

  if (!socket.IsOpen())
    return NetBase::SetErrorCode(result, NET_ERROR_INVALID_SOCKET);

  if (!socket.IsBound())
    return NetBase::SetErrorCode(result, NET_ERROR_INVALID_BIND);
  
  if (!socket.IsListening())
    return NetBase::SetErrorCode(result, NET_ERROR_INVALID_LISTEN);

  return NET_ERROR_OK;
}

std::shared_ptr<NetServerEvents> NetServer::GetEvents() const
{
  return this->m_events;
}

void NetServer::HandleSelect()
{
  
}

void NetServer::EnterLoop()
{
  std::thread{[]()
  {
    while (true)
    {
      auto action = NetActionQueue::PeekActionQueue();

      switch (action)
      {
      case NetAction::SERVER_STOP:
        goto finish;
      break;
      case NetAction::NONE:
        // TODO: Run typical server select
      break;
      }
    }
finish:;
  }}.detach();
}

NetClient::NetClient(std::string_view addr, int port)
    : NetBase(addr, port)
{ }

NetClient::~NetClient() = default;