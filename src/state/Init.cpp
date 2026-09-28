#include "./Init.h"

#include <asw/asw.h>

#include "../Controls.h"

void Init::init() {
  asw::display::set_title("Jim's Alien Adventure");
  asw::display::set_icon("assets/images/icon.png");

  controls::bind();
}

void Init::update(float dt) {
  Scene::update(dt);

  manager.set_next_scene(States::Intro);
}
