#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include <memory>
#include <utility>

#include "dispatcher.h"
#include "message_queue.h"
#include "sender.h"

namespace messaging {

/**
 * @brief 从消息队列
 *
 */
class Receiver {
 public:
  Receiver(std::shared_ptr<MessageQueue> q) : _q{std::move(q)} {}

  operator Sender() { return Sender{_q}; }

  Dispatcher wait() { return Dispatcher{_q}; }

 private:
  std::shared_ptr<MessageQueue> _q;
};
}  // namespace messaging

#endif  // _RECEIVER_H_