#ifndef INTRO_H
#define INTRO_H

#include "State.h"

#include <allegro.h>

// Intro screen of game
class Intro : public State {
 public:
  Intro();
  ~Intro();

  virtual void update(StateEngine* engine) override;
  virtual void draw(BITMAP* buffer) override;

 private:
  // Images
  BITMAP* splash;
  BITMAP* logo;

  // Time
  clock_t intro_time;
};

#endif  // INTRO_H
