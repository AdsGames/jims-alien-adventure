#include "Intro.h"

#include "tools.h"

Intro::Intro() {
  // Buffer
  splash = load_png_ex("images/splash.png");
  logo = load_png_ex("images/logo.png");

  // Start timer
  intro_time = clock();

  // Fade in title
  highcolor_fade_in (logo, 16);
}

Intro::~Intro() {
  // Clear memory
  destroy_bitmap (splash);
  destroy_bitmap (logo);

  // Fade out
  highcolor_fade_out (16);
}

void Intro::update(StateEngine *engine) {
  if (clock() - intro_time >= 3400 || keyboard_keypressed() || joy_buttonpressed()) {
    setNextState (engine, StateEngine::STATE_MENU);
  }
}

void Intro::draw(BITMAP *buffer) {
  if (clock() - intro_time < 1700) {
    stretch_sprite (buffer, logo, 0, 0, SCREEN_W, SCREEN_H);
  }
  else {
    stretch_sprite (buffer, splash, 0, 0, SCREEN_W, SCREEN_H);
  }
}
