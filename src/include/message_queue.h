#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>

#include "message_wrapper.h"

namespace messaging {

/**
 * @brief 线程安全的消息队列
 *
 */
class MessageQueue {
 public:
  std::shared_ptr<MessageBase> tryToPop();
  std::shared_ptr<MessageBase> waitAndPop();

  template <typename Msg>
  void push(const Msg &msg) {
    std::scoped_lock lock(_m);
    _q.push(std::make_shared<MessageWrapper<Msg>>(msg));
    _cond.notify_all();
  }

 private:
  std::mutex _m;
  std::condition_variable _cond;
  std::queue<std::shared_ptr<MessageBase>> _q;
};

}  // namespace messaging

#endif  // _MESSAGE_QUEUE_H_