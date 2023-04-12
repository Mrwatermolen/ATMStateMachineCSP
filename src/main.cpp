#include <thread>

#include "atm_message.h"
#include "atm_state_machine.h"
#include "bank_state_machine.h"
#include "gui_state_mchine.h"

int main() {
  Bank b{};
  Gui g{};
  ATM a{b.getSender(), g.getSender()};
  b.setATMSender(a.getSender());
  auto t1{std::thread{&Gui::run, &g}};
  auto t2{std::thread{&ATM::run, &a}};
  auto t3{std::thread{&Bank::run, &b}};
  while (true) {
    char c;
    std::cin >> c;
    if (c == 'i') {
      a.getSender().snedMsg(
          messaging::atm_message::CardInserted{"default_card"});
    }
    if (c == 'c') {
      a.getSender().snedMsg(messaging::atm_message::CancelInput{});
    }
    if (c == 'q') {
      break;
    }
    if (c == 'e') {
      a.getSender().snedMsg(messaging::atm_message::EnjectCard{});
    }
    if ('0' <= c && c <= '9') {
      a.getSender().snedMsg(messaging::atm_message::DigitPressed{c});
    }
  }
  g.done();
  a.done();
  b.done();
  t1.join();
  t2.join();
  t3.join();
}