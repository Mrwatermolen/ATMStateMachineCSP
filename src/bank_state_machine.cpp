#include "bank_state_machine.h"

#include "bank_state.h"
#include "dispatcher.h"

void Bank::run() {
  try {
    for (;;) {
      setState(new BankStateRunning{this});
      _state->action();
    }
  } catch (messaging::CloseQueueMsg &) {
  }
}