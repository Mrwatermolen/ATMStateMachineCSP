#ifndef _STATE_ATM_H_
#define _STATE_ATM_H_

#include <cstddef>

#include "atm_state_machine.h"
#include "state_base.h"

class ATMState : public StateBase {
 public:
  ATMState(ATM* atm) : _atm(atm) {}

 protected:
  template <typename Msg>
  void sendMsgToBank(const Msg& msg) {
    _atm->sendMsgToBank(msg);
  }

  template <typename Msg>
  void sendMsgToGui(const Msg& msg) {
    _atm->sendMsgToGui(msg);
  }

  std::string& getATMPIN() { return _atm->_pin; }
  std::string& getATMAccount() { return _atm->_account; }

  ATM* _atm;
};

class ATMStateWaitingForCard : public ATMState {
 public:
  ATMStateWaitingForCard(ATM* stateMachine) : ATMState(stateMachine){};
  void action() override;
};

class ATMStateGettingPIN : public ATMState {
 public:
  ATMStateGettingPIN(ATM* stateMachine) : ATMState(stateMachine){};
  void action() override;
};

class ATMStateWaitinfForVerifyPIN : public ATMState {
 public:
  ATMStateWaitinfForVerifyPIN(ATM* stateMachine) : ATMState(stateMachine){};
  void action() override;
};

class ATMStateOperatingAccount : public ATMState {
 public:
  ATMStateOperatingAccount(ATM* stateMachine) : ATMState(stateMachine){};
  void action() override;
};
#endif  // _STATE_ATM_H_