#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include <algorithm>
#include <memory>

#include "message_queue.h"
#include "message_wrapper.h"
#include "template_dispatcher.h"

namespace messaging {

/**
 * @brief 通知接收者消息队列已经关闭
 *
 */
struct CloseQueueMsg {};

/**
 * @brief 处理链表的首个元素，只处理CloseQueueMsg的消息，
 * 忽视其他消息，直到接受到处理CloseQueueMsg，抛出CloseQueueMsg异常
 *
 */
class Dispatcher {
  template <typename Msg, typename PrevoiusNode, typename Func>
  friend class TemplateDispatcher;

 public:
  explicit Dispatcher(std::shared_ptr<MessageQueue> q) : _q{std::move(q)} {};

  ~Dispatcher() noexcept(false);

  /**
   * @brief 创建处理链的处理消息的句柄
   *
   * @tparam Msg 处理的消息类型
   * @tparam Func
   * @param f 处理函数
   * @return TemplateDispatcher<Msg, Dispatcher, Func>
   * 处理Msg类型消息的TemplateDispatcher
   */
  template <typename Msg, typename Func>
  auto handle(Func &&f) -> TemplateDispatcher<Msg, Dispatcher, Func> {
    return TemplateDispatcher<Msg, Dispatcher, Func>{_q, this,
                                                     std::forward<Func>(f)};
  }

 private:
  std::shared_ptr<MessageQueue> _q;
  bool _chained{
      false};  // 是否在处理链中，如果是链尾元素则可视为不在处理链中，尾元素是处理消息的发起者

  /**
   * @brief 循环从消息队列中读取消息，会丢弃其他消息，除了CloseQueueMsg
   *
   */
  void waitAndDispatch();

  /**
   * @brief 处理CloseQueueMsg消息，抛出异常
   * @return false msg为非CloseQueueMsg 表明无法处理的消息 丢弃该消息
   */
  bool dispatch(std::shared_ptr<MessageBase> const &msg);
};

}  // namespace messaging

#endif  // _DISPATCHER_H_