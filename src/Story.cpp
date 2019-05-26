#include "Story.h"

#include "tools.h"
#include "globals.h"

// Constructor
Story::Story() {
  buffer = create_bitmap (SCREEN_W, SCREEN_H);
  story_splash = load_png_ex("images/story_splash.png");

  highcolor_fade_in (story_splash, 32);
  flasher = 0;
}

// Update
void Story::update(StateEngine *engine) {
  if (keyboard_keypressed() || joy_buttonpressed()) {
    setNextState (engine, StateEngine::STATE_MENU);
  }
}

// Draw
void Story::draw() {
  // Background
  draw_sprite (buffer, story_splash, 0, 0);

  // Any key flasher
  flasher = (flasher + 1) % flash_frequency;
  if (flasher > flash_frequency / 2) {
    textprintf_ex (buffer, font, 25, SCREEN_H - 50, makecol (0, 0, 0), -1, "PRESS ANY KEY TO CONTINUE");
  }

  // Buffer
  draw_sprite (screen, buffer, 0, 0);
}

// Destroy
Story::~Story() {
  // Destory Bitmaps
  destroy_bitmap (buffer);
  destroy_bitmap (story_splash);

  // Fade out
  highcolor_fade_out (32);
}
