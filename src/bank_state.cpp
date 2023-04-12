#include "bank_state.h"

#include <string>
#include <unordered_map>

#include "atm_message.h"
#include "bank_message.h"

using messaging::bank::VerifyPIN;

static std::unordered_map<std::string, std::string> accountData{
    {"default_card", "1234"}};

void BankStateRunning::action() {
  _bank->getDispatcher().handle<VerifyPIN>([&](const VerifyPIN& msg) {
    auto pin{accountData.find(msg._account)};
    if (pin == accountData.end() || pin->second != msg._pin) {
      _bank->sendMsgToATM(
          messaging::atm_message::PINIncorrect{msg._account, msg._id});
      return;
    }

    _bank->sendMsgToATM(
        messaging::atm_message::PINValided{msg._account, msg._id});
  });
}