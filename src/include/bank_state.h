#ifndef _BANK_STATE_H_
#define _BANK_STATE_H_

#include "bank_state_machine.h"
#include "state_base.h"

class BankState : public StateBase {
 public:
  BankState(Bank* bank) : _bank{bank} {}

 protected:
  Bank* _bank;
};

class BankStateRunning : public BankState {
 public:
  BankStateRunning(Bank* bank) : BankState(bank){};
  void action() override;
};

#endif  // _BANK_STATE_H_