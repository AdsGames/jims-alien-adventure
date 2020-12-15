#include "Story.h"

#include "tools.h"

// Constructor
Story::Story() {
  story_splash = load_png_ex("images/story_splash.png");
  flasher = 0;
  highcolor_fade_in(story_splash, 32);
}

// Destroy
Story::~Story() {
  destroy_bitmap(story_splash);
  highcolor_fade_out(32);
}

// Update
void Story::update(StateEngine* engine) {
  if (key_down() || button_down()) {
    setNextState(engine, StateEngine::STATE_MENU);
  }

  flasher = (flasher + 1) % flash_frequency;
}

void Story::draw(BITMAP* buffer) {
  // Background
  draw_sprite(buffer, story_splash, 0, 0);

  // Any key flasher
  if (flasher > flash_frequency / 2) {
    textprintf_ex(buffer, font, 25, SCREEN_H - 50, makecol(0, 0, 0), -1,
                  "PRESS ANY KEY TO CONTINUE");
  }
}
