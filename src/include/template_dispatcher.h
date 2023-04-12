#ifndef _TEMPLATE_DISPATCHER_H_
#define _TEMPLATE_DISPATCHER_H_

#include <utility>

#include "message_queue.h"
#include "message_wrapper.h"

namespace messaging {

/**
 * @brief 处理链中的元素，如果无法处理消息，将消息交给上一元素
 *
 * @tparam Msg 能处理的消息类型
 * @tparam PrevoiusNode 处理链中的上一个元素
 * @tparam Func 消息处理函数
 */
template <typename Msg, typename PrevoiusNode, typename Func>
class TemplateDispatcher {
  template <typename OtherMsg, typename Dispatcher, typename OtherFunc>
  friend class TemplateDispatcher;

 public:
  TemplateDispatcher(std::shared_ptr<MessageQueue> q, PrevoiusNode *prevNode,
                     Func &&f)
      : _q{std::move(q)}, _prevNode{prevNode}, _f{std::forward<Func>(f)} {
    prevNode->_chained = true;  // 将prevNode加入消息链中
  }

  ~TemplateDispatcher() {
    if (!_chained) {
      // 链尾元素读取消息
      waitAndDispatch();
    }
  }

  TemplateDispatcher(const TemplateDispatcher &) = delete;
  TemplateDispatcher &operator=(const TemplateDispatcher &) = delete;

  /**
   * @brief 创建处理链的处理消息的句柄
   *
   * @tparam OtherMsg
   * @tparam OtherFunc
   * @param f
   * @return TemplateDispatcher<OtherMsg, TemplateDispatcher, OtherFunc>
   */
  template <typename OtherMsg, typename OtherFunc>
  auto handle(OtherFunc &&f)
      -> TemplateDispatcher<OtherMsg, TemplateDispatcher, OtherFunc> {
    return TemplateDispatcher<OtherMsg, TemplateDispatcher, OtherFunc>{
        _q, this, std::forward<OtherFunc>(f)};
  }

 private:
  std::shared_ptr<MessageQueue> _q;
  PrevoiusNode *_prevNode;
  Func _f;
  bool _chained{false};  // 是否为链尾元素 false为链尾元素

  /**
   * @brief 循环从消息队列中读取消息，直至成功处理一次消息
   *
   */
  void waitAndDispatch() {
    while (true) {
      if (dispatch(_q->waitAndPop())) {
        break;
      }
    }
  }

  /**
   * @brief 尝试处理传人的消息，无法处理则交给上一个元素
   *
   * @param msg
   * @return true 处理链中从该节点开始到头元素有元素能够处理该消息
   * @return false 处理链中从该节点开始到头元素没有元素能够处理该消息
   */
  bool dispatch(std::shared_ptr<MessageBase> const &msg) {
    if (auto p{dynamic_cast<MessageWrapper<Msg> *>(msg.get())}; p != nullptr) {
      _f(p->getContent());
      return true;
    }

    return _prevNode->dispatch(msg);  // 将消息交给上一个元素处理
  }
};

}  // namespace messaging

#endif  // _TEMPLATE_DISPATCHER_H_