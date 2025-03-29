#include "./Intro.h"

void Intro::init() {
  // Buffer
  splash = asw::assets::loadTexture("assets/images/splash.png");
  logo = asw::assets::loadTexture("assets/images/logo.png");

  // Start timer
  timer.start();
}

void Intro::update(float deltaTime) {
  Scene::update(deltaTime);

  if (timer.getElapsedTime<std::chrono::milliseconds>() >= 3400 ||
      asw::input::keyboard.anyPressed || asw::input::mouse.anyPressed) {
    sceneManager.setNextScene(States::Menu);
  }
}

void Intro::draw() {
  if (timer.getElapsedTime<std::chrono::milliseconds>() < 1700) {
    asw::draw::stretchSprite(
        logo, asw::Quad<float>(0, 0, asw::display::getLogicalSize().x,
                               asw::display::getLogicalSize().y));
  } else {
    asw::draw::stretchSprite(
        splash, asw::Quad<float>(0, 0, asw::display::getLogicalSize().x,
                                 asw::display::getLogicalSize().y));
  }
}
