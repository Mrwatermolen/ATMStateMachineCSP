#ifndef _BANK_MESSAGE_H_
#define _BANK_MESSAGE_H_

#include <cstddef>
#include <string>
#include <utility>

namespace messaging::bank {
struct VerifyPIN {
  VerifyPIN(std::string account, std::string pin, size_t id)
      : _account{std::move(account)}, _pin{std::move(pin)}, _id{id} {};
  std::string _account;
  std::string _pin;
  size_t _id;
};
}  // namespace messaging::bank

#endif  // _BANK_MESSAGE_H_