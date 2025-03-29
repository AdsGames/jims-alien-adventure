#include "./Story.h"

#include "../tools.h"

// Constructor
void Story::init() {
  story_splash = asw::assets::loadTexture("assets/images/story_splash.png");
  font = asw::assets::loadFont("assets/fonts/dosis.ttf", 24);
  text_position = asw::Vec2<float>(25, asw::display::getSize().y - 50);
}

// Update
void Story::update(float deltaTime) {
  Scene::update(deltaTime);

  if (asw::input::keyboard.anyPressed) {
    sceneManager.setNextScene(States::Menu);
  }

  flasher += deltaTime;
  if (flasher > flash_frequency) {
    flasher = 0;
  }
}

void Story::draw() {
  Scene::draw();

  // Background
  asw::draw::sprite(story_splash, asw::Vec2<float>(0, 0));

  // Any key flasher
  if (flasher < flash_frequency / 2) {
    asw::draw::text(font, "PRESS ANY KEY TO CONTINUE", text_position,
                    asw::util::makeColor(0, 0, 0));
  }
}
