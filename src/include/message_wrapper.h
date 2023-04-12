#ifndef _MESSAGE_WRAPPER_H_
#define _MESSAGE_WRAPPER_H_

#include <utility>

namespace messaging {

/**
 * @brief 消息载体的抽象基类
 *
 */
class MessageBase {
 public:
  virtual ~MessageBase() = default;
};

/**
 * @brief 消息载体
 *
 * @tparam Msg 消息类型
 */
template <typename Msg>
class MessageWrapper : public MessageBase {
 public:
  explicit MessageWrapper(const Msg& content) : _content{content} {};

  /**
   * @brief 获取具体的消息内容
   */
  Msg getContent() const { return _content; }

 private:
  Msg _content;
};

}  // namespace messaging

#endif  // _MESSAGE_WRAPPER_H_