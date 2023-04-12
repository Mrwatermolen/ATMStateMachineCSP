#ifndef _GUI_STATE_MCHINE_H_
#define _GUI_STATE_MCHINE_H_

#include "state_machine.h"

class Gui : public StateMachineBase {
 public:
  void run() override;

  ~Gui() override = default;

 private:
};

#endif  // _GUI_STATE_MCHINE_H_