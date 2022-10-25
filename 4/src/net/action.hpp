#ifndef ACTION_HPP
#define ACTION_HPP

#include <queue>
#include <mutex>

enum class NetAction : int
{
  // Server-based actions
  SERVER_STOP,

  // Command-based actions
  COMMAND_EXIT_THREAD,

  NONE
};

class NetActionQueue
{
  inline static auto m_mutex = std::mutex{};
  inline static auto m_action_queue = std::queue<NetAction>{};

public:
  static void PushToActionQueue(NetAction action);
  static NetAction PeekActionQueue();
  static NetAction PopActionQueue();
};

#endif