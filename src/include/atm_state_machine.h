#ifndef _ATM_STATE_MACHINE_H_
#define _ATM_STATE_MACHINE_H_

#include <cstddef>
#include <memory>
#include <utility>

#include "message_queue.h"
#include "receiver.h"
#include "sender.h"
#include "state_base.h"
#include "state_machine.h"

constexpr size_t ATM_VAILED_PIN_LENGTH{4UL};

class ATM : public StateMachineBase {
  friend class ATMState;

 public:
  ATM(messaging::Sender bankSender, messaging::Sender guiSender);

  ~ATM() override = default;

  void run() override;

  void initState();

  size_t generateRequestID() { return ++_mark; }

  bool isMatchedMsg(const size_t id) const { return id == _mark; }

 private:
  messaging::Sender _bank;
  messaging::Sender _gui;
  std::string _account{};
  std::string _pin{};
  size_t _mark{0UL};

  template <typename Msg>
  void sendMsgToBank(const Msg& msg) {
    _bank.snedMsg(msg);
  }

  template <typename Msg>

  void sendMsgToGui(const Msg& msg) {
    _gui.snedMsg(msg);
  }
};

#endif  // _ATM_STATE_MACHINE_H_