#ifndef _SENDER_H_
#define _SENDER_H_

#include <memory>
#include <utility>

#include "message_queue.h"
namespace messaging {
class Sender {
 public:
  Sender() = default;
  explicit Sender(std::shared_ptr<MessageQueue> q) : _q{std::move(q)} {}
  explicit Sender(const Sender& others) = default;
  explicit Sender(Sender&& others) noexcept : _q{std::move(others._q)} {}
  Sender& operator=(const Sender& others) {
    if (this == &others) {
      return *this;
    }
    _q = others._q;
    return *this;
  }

  template <typename Msg>
  void snedMsg(const Msg& msg) {
    // messaging::MessageQueue::push<messaging::CloseQueueMsg>
    _q->push(msg);
  }

 private:
  std::shared_ptr<MessageQueue> _q{};
};
}  // namespace messaging

#endif  // _SENDER_H_