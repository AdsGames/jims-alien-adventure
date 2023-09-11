#ifndef STORY_H
#define STORY_H

#include "State.h"

#include <asw/asw.h>

class Story : public State {
 public:
  Story();

  virtual void update(StateEngine* engine) override;
  virtual void draw() override;

 private:
  const char flash_frequency = 30;
  char flasher;
  asw::Texture story_splash;
  asw::Font font;
};

#endif  // STORY_H
