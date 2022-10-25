#ifndef NETLIB_HPP
#define NETLIB_HPP

#ifdef WIN32
// Definitions required on Windows systems (MSVC?)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <ws2tcpip.h>
#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")
using NetSocketType = SOCKET;
#define socketclose closesocket
#endif
#ifdef UNIX
// Definitions required on UNIX systems (POSIX)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
using NetSocketType = int;
#define socketclose close
#endif

#include <string_view>

/* Cross-platform wrapper around socket apis */
class NetTCPSocket
{
  NetSocketType m_socket; // Raw socket
  bool m_bound = false; // Successfully bound?
  bool m_listening = false; // Successfully listening?
  fd_set m_set{};

public:
  static void StartupSockets();
  static void ShutdownSockets();

  NetTCPSocket(std::string_view addr, int port);
  ~NetTCPSocket();

  bool IsOpen() const;
  bool IsBound() const;
  bool IsListening() const;
};

#endif