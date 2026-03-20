#include "./Story.h"

// Constructor
void Story::init() {
  story_splash = asw::assets::load_texture("assets/images/story_splash.png");
  font = asw::assets::load_font("assets/fonts/dosis.ttf", 24);
  text_position = asw::Vec2f(25, asw::display::get_logical_size().y - 50);
}

// Update
void Story::update(float dt) {
  Scene::update(dt);

  if (asw::input::keyboard.any_pressed) {
    manager.set_next_scene(States::Menu);
  }

  flasher += dt;
  if (flasher > flash_frequency) {
    flasher = 0;
  }
}

void Story::draw() {
  Scene::draw();

  // Background
  asw::draw::sprite(story_splash, asw::Vec2f(0, 0));

  // Any key flasher
  if (flasher < flash_frequency / 2) {
    asw::draw::text(font, "PRESS ANY KEY TO CONTINUE", text_position,
                    asw::Color(0, 0, 0));
  }
}
