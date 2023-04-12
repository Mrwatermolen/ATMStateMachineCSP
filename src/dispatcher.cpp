#include "dispatcher.h"

using messaging::Dispatcher;

Dispatcher::~Dispatcher() noexcept(false) {
  if (!_chained) {
    // 是处理链中的链尾元素，开始读取消息队列
    waitAndDispatch();
  }
}

void messaging::Dispatcher::waitAndDispatch() {
  while (true) {
    dispatch(_q->waitAndPop());
  }
}

bool Dispatcher::dispatch(std::shared_ptr<messaging::MessageBase> const &msg) {
  if (auto p{
          dynamic_cast<messaging::MessageWrapper<messaging::CloseQueueMsg> *>(
              msg.get())};
      p != nullptr) {
    throw messaging::CloseQueueMsg();
  }
  return false;
}