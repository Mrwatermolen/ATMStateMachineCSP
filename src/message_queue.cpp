#include "message_queue.h"

#include <mutex>

std::shared_ptr<messaging::MessageBase> messaging::MessageQueue::waitAndPop() {
  std::unique_lock lock{_m};
  _cond.wait(lock, [&]() -> bool { return !_q.empty(); });
  auto res{_q.front()};
  _q.pop();
  return res;
}

std::shared_ptr<messaging::MessageBase> messaging::MessageQueue::tryToPop() {
  std::scoped_lock lock{_m};
  if (_q.empty()) {
    return {};
  }

  auto res{_q.front()};
  _q.pop();
  return res;
}