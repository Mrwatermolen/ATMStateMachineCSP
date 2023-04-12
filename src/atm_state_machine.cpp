#include "atm_state_machine.h"

#include <exception>

#include "atm_state.h"
#include "dispatcher.h"

ATM::ATM(messaging::Sender bank, messaging::Sender gui)
    : _bank{std::move(bank)}, _gui{std::move(gui)} {}

void ATM::run() {
  initState();
  try {
    for (;;) {
      _state->action();
    }
  } catch (const messaging::CloseQueueMsg &e) {
  }
}

void ATM::initState() {
  _account.clear();
  _pin.clear();
  setState(new ATMStateWaitingForCard(this));
}