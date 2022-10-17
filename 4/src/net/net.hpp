#ifndef NET_HPP
#define NET_HPP

#include <string_view>
#include <functional>
#include <memory>

/* Enum for representing errors in an integer bitflag */
enum NetErrorCode
{
  NET_ERROR_OK = 0,
  NET_ERROR_INVALID_SOCKET = 1 << 0
}

/* Base class for network entities that have addresses and ports */
template<typename EventsType> // Type for events handling
class NetBase
{
protected:
  std::shared_ptr<EventsType> m_events = nullptr;
  std::string_view m_addr{};
  int m_port = 52000;

  static int SetErrorCode(int current, int code);
  static int UnsetErrorCode(int current, int code);

public:
  NetBase(std::string_view addr, int port);
  ~NetBase();

  std::string_view GetAddress() const;  // Returns the network entity's address (host)
  int GetPort() const;                  // Returns the network entity's port
};

/* Generic network event */
template<typename ... Types>
using NetEvent = std::function<void(Types...)>;

/* Structure to hold server-specific network events */
struct NetServerEvents
{
  NetEvent<std::string_view, int> m_startup;    // Called on server startup
  NetEvent<void> m_connect;                     // Called on server connect
  NetEvent<void> m_bind;                        // Called on server bind
  NetEvent<void> m_accept;                      // Called on server accept
};

/* Network entitiy specialization for server */
class NetServer : public NetBase<NetServerEvents>
{
public:
  NetServer(int port);
  ~NetServer();

  int StartServer();                                    // Starts the server loop (opens a socket)
  std::shared_ptr<NetServerEvents> GetEvents() const;   // Returns bound events for this entity
  void StopServer();                                    // Stops the server loop (closes the socket)
};

struct NetClientEvents
{
  NetEvent<void> m_connect; // Called when client connects to server
};

class NetClient : public NetBase<NetClientEvents>
{
public:
  NetClient(std::string_view addr, int port);
  ~NetClient();
};

#endif