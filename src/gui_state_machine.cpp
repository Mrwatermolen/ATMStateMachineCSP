#include <exception>

#include "dispatcher.h"
#include "gui_message.h"
#include "gui_state.h"
#include "gui_state_mchine.h"

void Gui::run() {
  setState(new GuiStateDisplay{this});
  try {
    for (;;) {
      _state->action();
    }
  } catch (const messaging::CloseQueueMsg &) {
  }
}