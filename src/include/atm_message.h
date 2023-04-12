#ifndef _ATM_MESSAGE_H_
#define _ATM_MESSAGE_H_

#include <cstddef>
#include <string>
#include <utility>

namespace messaging::atm_message {
struct CardInserted {
  std::string _account;
  explicit CardInserted(std::string account) : _account{std::move(account)} {};
};

struct DigitPressed {
  char _digit;
  explicit DigitPressed(char digit) : _digit{digit} {}
};

struct PINValided {
  std::string _account;
  size_t _id;
  explicit PINValided(std::string account, size_t id)
      : _account{std::move(account)}, _id{id} {};
};

struct PINIncorrect {
  std::string _account;
  size_t _id;
  explicit PINIncorrect(std::string account, size_t id)
      : _account{std::move(account)}, _id{id} {};
};

struct CancelInput {};

struct EnjectCard {};
}  // namespace messaging::atm_message

#endif  // _ATM_MESSAGE_H_