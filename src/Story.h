#ifndef STORY_H
#define STORY_H

#include "State.h"

#include <allegro.h>

class Story : public State {
 public:
  Story();
  ~Story();

  virtual void update(StateEngine* engine) override;
  virtual void draw(BITMAP* buffer) override;

 private:
  const char flash_frequency = 30;
  char flasher;
  BITMAP* story_splash;
};

#endif  // STORY_H
