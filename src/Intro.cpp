#include "Intro.h"

#include "tools.h"

Intro::Intro() {
  // Buffer
  splash = asw::assets::loadTexture("assets/images/splash.png");
  logo = asw::assets::loadTexture("assets/images/logo.png");

  // Start timer
  timer.start();
}

void Intro::update(StateEngine* engine) {
  if (timer.getElapsedTime<std::chrono::milliseconds>() >= 3400 ||
      asw::input::keyboard.anyPressed || asw::input::mouse.anyPressed) {
    setNextState(engine, StateEngine::STATE_MENU);
  }
}

void Intro::draw() {
  if (timer.getElapsedTime<std::chrono::milliseconds>() < 1700) {
    asw::draw::stretchSprite(logo, 0, 0, asw::display::getSize().x,
                             asw::display::getSize().y);
  } else {
    asw::draw::stretchSprite(splash, 0, 0, asw::display::getSize().x,
                             asw::display::getSize().y);
  }
}
