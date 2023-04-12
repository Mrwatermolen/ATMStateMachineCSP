#ifndef _STATE_H_
#define _STATE_H_

#include "message_queue.h"

class StateBase {
 public:
  virtual ~StateBase() = default;

  virtual void action() = 0;

};

#endif  // _STATE_H_