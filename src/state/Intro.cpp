#include "./Intro.h"

void Intro::init() {
  // Buffer
  splash = asw::assets::load_texture("assets/images/splash.png");
  logo = asw::assets::load_texture("assets/images/logo.png");
}

void Intro::update(float dt) {
  Scene::update(dt);
  const auto& mouse = asw::input::get_mouse();
  const auto& keyboard = asw::input::get_keyboard();

  timer += dt;

  if (timer >= 3.4F || keyboard.any_pressed || mouse.any_pressed) {
    manager.set_next_scene(States::Menu);
  }
}

void Intro::draw() {
  const auto logicalSize = asw::display::get_logical_size();

  if (timer < 1.7F) {
    asw::draw::stretch_sprite(logo,
                              asw::Quadf(0, 0, logicalSize.x, logicalSize.y));
  } else {
    asw::draw::stretch_sprite(splash,
                              asw::Quadf(0, 0, logicalSize.x, logicalSize.y));
  }
}
