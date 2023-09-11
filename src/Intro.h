#ifndef INTRO_H
#define INTRO_H

#include "State.h"

#include <asw/asw.h>
#include <asw/util/Timer.h>

// Intro screen of game
class Intro : public State {
 public:
  Intro();

  virtual void update(StateEngine* engine) override;
  virtual void draw() override;

 private:
  // Images
  asw::Texture splash;
  asw::Texture logo;

  // Time
  Timer timer;
};

#endif  // INTRO_H
