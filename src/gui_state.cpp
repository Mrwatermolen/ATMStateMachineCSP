#include "gui_state.h"

#include <iostream>

#include "gui_message.h"

void GuiStateDisplay::action() {
  _gui->getDispatcher()
      .handle<messaging::DisplayGetPIN>(
          [&](const messaging::DisplayGetPIN& msg) {
            std::cout << "Please input your PIN (0-9)" << std::endl;
          })
      .handle<messaging::DisplayEnterCard>(
          [&](const messaging::DisplayEnterCard& msg) {
            std::cout << "Please enter card (i)" << std::endl;
          })
      .handle<messaging::DisplayOperate>(
          [&](const messaging::DisplayOperate& msg) {
            std::cout << "Operate Account:" << msg._account << std::endl;
            std::cout << "Enject Card " << msg._account << " (e)" << std::endl;
          });
}