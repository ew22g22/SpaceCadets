#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <protocol.hpp>
#include <netlib.hpp>
#include <thread>
#include <deque>
#include <mutex>
#include <string>

class Client
{
  std::string_view m_addr{};
  int m_port;
  NetSocketType m_raw_socket;
  
  inline static std::mutex m_mutex{};
  inline static std::deque<std::string> m_buf_queue{};

  void TickClient()
  {
    if (m_buf_queue.empty())
      return;

    m_mutex.lock();
    auto buf = m_buf_queue.pop_front();
    m_mutex.unlock();
  }

  static void HandleInput()
  {
    int c;
    std::string buf{};

    while (true)
    {
      while ((c = getchar()) != '\n' && c != EOF)
        buf.push_back(c);
      
      m_mutex.lock();
      m_buf_queue.emplace_back(buf);
      m_mutex.unlock();
      buf.clear();
    }
  }

public:
  Client(std::string_view m_addr, int m_port)
  {
    this->m_raw_socket = netlib::CreateSocket();
    
    if (this->m_raw_socket == INVALID_SOCKET)
      return;
    
    auto res = netlib::Connect(this->m_raw_socket, this->m_addr, this->m_port);

    if (res == SOCKET_ERROR)
      return;
    
    std::thread{ HandleInput }.detach();

    while (true)
    {
        this->TickClient();
    }
  }

  ~Client()
  {
    netlib::CloseSocket(this->m_raw_socket);
    netlib::ShutdownNetlib();
  }
};

#endif