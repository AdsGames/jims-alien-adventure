#include "./Init.h"

#include <asw/asw.h>

#include "../LevelData.h"

void Init::init() {
  asw::display::set_title("Jim's Alien Adventure");
  asw::display::set_icon("assets/images/icon.png");

  // Action bindings
  using namespace asw::input;
  bind_action("up", ActionBinding{KeyBinding{Key::Up}});
  bind_action("up",
              ActionBinding{ControllerButtonBinding{ControllerButton::Y, 0}});

  bind_action("down", ActionBinding{KeyBinding{Key::Down}});
  bind_action("down",
              ActionBinding{ControllerButtonBinding{ControllerButton::A, 0}});

  bind_action("left", ActionBinding{KeyBinding{Key::Left}});
  bind_action("left",
              ActionBinding{ControllerButtonBinding{ControllerButton::X, 0}});

  bind_action("right", ActionBinding{KeyBinding{Key::Right}});
  bind_action("right",
              ActionBinding{ControllerButtonBinding{ControllerButton::B, 0}});
}

void Init::update(float dt) {
  Scene::update(dt);

  manager.set_next_scene(States::Intro);
}
