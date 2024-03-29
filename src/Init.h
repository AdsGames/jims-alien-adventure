#ifndef INIT_H
#define INIT_H

#include "State.h"

class Init : public State {
 public:
  Init();

  virtual void update(StateEngine* engine) override;
  virtual void draw() override;
};

#endif  // INIT_H
