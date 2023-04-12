#ifndef _GUI_STATE_H_
#define _GUI_STATE_H_

#include "gui_state_mchine.h"
#include "state_base.h"

class GuiState : public StateBase {
 public:
  explicit GuiState(Gui* gui) : _gui{gui} {};

 protected:
  Gui* _gui;
};

class GuiStateDisplay : public GuiState {
 public:
  explicit GuiStateDisplay(Gui* gui) : GuiState{gui} {};
  void action() override;
};

#endif  // _GUI_STATE_H_