#include "action.hpp"

void NetActionQueue::PushToActionQueue(NetAction action)
{
  m_mutex.lock();
  m_action_queue.push(action);
  m_mutex.unlock();
}

NetAction NetActionQueue::PeekActionQueue()
{
  m_mutex.lock();

  if (m_action_queue.empty())
  {
    m_mutex.unlock();
    return NetAction::NONE;
  }

  NetAction action = m_action_queue.front();
  m_mutex.unlock();
  return action;
}

NetAction NetActionQueue::PopActionQueue()
{
  m_mutex.lock();

  if (m_action_queue.empty())
  {
    m_mutex.unlock();
    return NetAction::NONE;
  }

  NetAction action = m_action_queue.front();
  m_action_queue.pop();
  m_mutex.unlock();
  return action;
}