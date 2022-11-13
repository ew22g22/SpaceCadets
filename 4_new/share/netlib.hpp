#ifndef NETLIB_HPP
#define NETLIB_HPP

#ifdef _WIN32
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
#define readsocket(a, b, c) recv(a, b, c, 0)
#endif
#if (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
// Definitions required on POSIX systems
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
using NetSocketType = int;
#define socketclose close
#define readsocket read
#endif

#include <string_view>
#include <functional>

namespace netlib
{
  // WSA sucks.
  inline void StartupNetlib()
  {
#ifdef _WIN32
    auto ver = MAKEWORD(2, 2);
    WSADATA data{};
    WSAStartup(ver, &data);
#endif
  }

  inline void ShutdownNetlib()
  {
#ifdef _WIN32
    WSACleanup();
#endif
  }

  inline NetSocketType CreateSocket()
  {
    return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  }

  inline void CloseSocket(NetSocketType socket)
  {
    socketclose(socket);
  }

  inline bool BindSocket(NetSocketType socket, std::string_view addr, int port)
  {
    sockaddr_in hint{};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(socket, addr.data(), &hint.sin_addr);

    return bind(socket, reinterpret_cast<sockaddr*>(&hint), sizeof hint) == 0;
  }

  inline bool ListenSocket(NetSocketType socket)
  {
    return listen(socket, SOMAXCONN) == 0;
  }

  inline int SelectSocket(fd_set &set)
  {
#ifdef _WIN32
    return select(0, &set, nullptr, nullptr, nullptr);
#endif
#if (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    select(FD_SETSIZE, &set, nullptr, nullptr, nullptr);
    return FD_SETSIZE;
#endif
  }

  inline bool CheckIfSet(fd_set &set, int i)
  {
#ifdef _WIN32
    return true;
#endif
#if (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    return FD_ISSET(i, &set);
#endif
  }

  inline NetSocketType GetSelectResult(fd_set &set, int i)
  {
#ifdef _WIN32
    return set.fd_array[i];
#endif
#if (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    return i;
#endif
  }

  inline NetSocketType Accept(NetSocketType socket)
  {
    return accept(socket, nullptr, nullptr);
  }

  template<typename T>
  inline int Read(NetSocketType socket, T *buf, int n)
  {
    return readsocket(socket, (char *) buf, n);
  }

  inline int Connect(NetSocketType socket, std::string_view addr, int port)
  {
    sockaddr_in hint{};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(socket, addr.data(), &hint.sin_addr);

    return connect(socket, reinterpret_cast<sockaddr*>(&hint), sizeof hint);
  }
}

/* Generic event wrapper */
template<typename ... Types>
using Event = void(*)(Types...);

#endif