#ifndef NETLIB_HPP
#define NETLIB_HPP

#ifdef WIN32
// Definitions required on Windows systems (MSVC?)
#include <windows.h>
#include <ws2tcpip.h>
#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")
using NetSocketType = SOCKET;
#endif
#ifdef UNIX
// Definitions required on UNIX systems (POSIX)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
using NetSocketType = int;
#endif

/* Cross-platform wrapper around socket apis */
class NetTCPSocket
{
  NetSocketType m_socket; // Raw socket

public:
  static void StartupSockets();
  static void ShutdownSockets();

  NetTCPSocket(std::string_view addr, int port);
  ~NetTCPSocket();

  bool IsOpen() const;
};

#endif