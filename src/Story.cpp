#include "Story.h"

#include "tools.h"

// Constructor
Story::Story() {
  story_splash = asw::assets::loadTexture("assets/images/story_splash.png");
  flasher = 0;
  font = asw::assets::loadFont("assets/fonts/dosis.ttf", 24);
}

// Update
void Story::update(StateEngine* engine) {
  if (asw::input::keyboard.anyPressed) {
    setNextState(engine, StateEngine::STATE_MENU);
  }

  flasher = (flasher + 1) % flash_frequency;
}

void Story::draw() {
  // Background
  asw::draw::sprite(story_splash, 0, 0);

  // Any key flasher
  if (flasher > flash_frequency / 2) {
    asw::draw::text(font, "PRESS ANY KEY TO CONTINUE", 25,
                    asw::display::getSize().y - 50,
                    asw::util::makeColor(0, 0, 0));
  }
}
