#ifndef _GUI_MESSAGE_H_
#define _GUI_MESSAGE_H_

#include <string>
#include <string_view>

namespace messaging {

struct DisplayEnterCard {};

struct DisplayGetPIN {
  explicit DisplayGetPIN(std::string_view account) : _account{account} {}

  std::string _account;
};

struct DisplayOperate {
  explicit DisplayOperate(std::string_view account) : _account{account} {}

  std::string _account;
};

}  // namespace messaging
#endif  // _GUI_MESSAGE_H_