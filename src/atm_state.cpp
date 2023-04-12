#include "atm_state.h"

#include <iostream>

#include "atm_message.h"
#include "atm_state_machine.h"
#include "bank_message.h"
#include "gui_message.h"

using messaging::atm_message::CancelInput;

void ATMStateWaitingForCard::action() {
  using messaging::atm_message::CardInserted;

  sendMsgToGui(messaging::DisplayEnterCard{});
  _atm->getDispatcher().handle<CardInserted>([&](const CardInserted &msg) {
    getATMAccount() = msg._account;
    sendMsgToGui(messaging::DisplayGetPIN{msg._account});
    _atm->setState(new ATMStateGettingPIN{_atm});
  });
}

void ATMStateGettingPIN::action() {
  using messaging::atm_message::DigitPressed;
  using messaging::bank::VerifyPIN;

  _atm->getDispatcher()
      .handle<DigitPressed>([&](const DigitPressed &msg) {
        auto &currentPin{this->getATMPIN()};
        currentPin += msg._digit;
        if (currentPin.length() < ATM_VAILED_PIN_LENGTH) {
          _atm->setState(new ATMStateGettingPIN(_atm));
          return;
        }

        sendMsgToBank(
            VerifyPIN{getATMAccount(), currentPin, _atm->generateRequestID()});
        currentPin.clear();
        _atm->setState(new ATMStateWaitinfForVerifyPIN(_atm));
      })
      .handle<CancelInput>([&](const CancelInput &msg) {
        this->getATMPIN().clear();
        _atm->setState(new ATMStateGettingPIN(_atm));
      });
}

void ATMStateWaitinfForVerifyPIN::action() {
  using messaging::atm_message::PINIncorrect;
  using messaging::atm_message::PINValided;

  _atm->getDispatcher()
      .handle<PINIncorrect>([&](const PINIncorrect &msg) {
        if (!_atm->isMatchedMsg(msg._id)) {
          return;
        }
        sendMsgToGui(messaging::DisplayGetPIN{msg._account});
        _atm->setState(new ATMStateGettingPIN{_atm});
      })
      .handle<PINValided>([&](const PINValided &msg) {
        if (!_atm->isMatchedMsg(msg._id)) {
          return;
        }
        sendMsgToGui(messaging::DisplayOperate{msg._account});
        _atm->setState(new ATMStateOperatingAccount{_atm});
      });
}

void ATMStateOperatingAccount::action() {
  using messaging::atm_message::EnjectCard;
  _atm->getDispatcher().handle<messaging::atm_message::EnjectCard>(
      [&](const EnjectCard &msg) { _atm->initState(); });
}