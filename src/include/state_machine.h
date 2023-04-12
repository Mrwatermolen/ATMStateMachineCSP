#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include <memory>

#include "dispatcher.h"
#include "message_queue.h"
#include "receiver.h"
#include "sender.h"
#include "state_base.h"

class StateMachineBase {
 public:
  StateMachineBase()
      : _incoming{std::move(std::make_shared<messaging::MessageQueue>())} {}

  StateMachineBase(const StateMachineBase &) = delete;
  StateMachineBase &operator=(const StateMachineBase &) = delete;
  virtual ~StateMachineBase() = default;

  virtual void run() = 0;

  void done() { getSender().snedMsg(messaging::CloseQueueMsg()); };

  messaging::Sender getSender() { return _incoming; }

  messaging::Dispatcher getDispatcher() { return _incoming.wait(); };

  void setState(StateBase *state) { _state.reset(state); }

 protected:
  std::unique_ptr<StateBase> _state{};

 private:
  messaging::Receiver _incoming;
};

#endif  // _STATE_MACHINE_H_