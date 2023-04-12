#ifndef _BANK_STATE_MACHINE_H_
#define _BANK_STATE_MACHINE_H_

#include <algorithm>

#include "sender.h"
#include "state_machine.h"

class Bank : public StateMachineBase {
 public:
  void run() override;

  bool isValidedPIN();
  void setATMSender(const messaging::Sender& ATMSender) {
    _ATMSender = ATMSender;
  }

  template <typename Msg>
  void sendMsgToATM(const Msg& msg) {
    _ATMSender.snedMsg(msg);
  };

 private:
  messaging::Sender _ATMSender;
};

#endif  // _BANK_STATE_MACHINE_H_