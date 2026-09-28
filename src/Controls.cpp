#include "Controls.h"

#include <asw/asw.h>
#include <string>

namespace {
using asw::input::ControllerAxis;
using asw::input::ControllerAxisBinding;
using asw::input::ControllerButton;
using asw::input::ControllerButtonBinding;
using asw::input::Key;
using asw::input::KeyBinding;

constexpr auto ANY = asw::input::ANY_CONTROLLER;

// Stick must pass this before it counts as a direction
constexpr float STICK_THRESHOLD = 0.5F;

void bind_key(const std::string& name, Key key, ControllerButton button) {
  asw::input::bind_action(name, KeyBinding{key});
  asw::input::bind_action(name, ControllerButtonBinding{button, ANY});
}

void bind_direction(const std::string& name,
                    Key key,
                    ControllerButton dpad,
                    ControllerAxis axis,
                    bool positive) {
  bind_key(name, key, dpad);
  asw::input::bind_action(
      name, ControllerAxisBinding{axis, ANY, STICK_THRESHOLD, positive});
}
}  // namespace

void controls::bind() {
  // Face buttons match the controller key images
  bind_key(UP, Key::Up, ControllerButton::Y);
  bind_key(DOWN, Key::Down, ControllerButton::A);
  bind_key(LEFT, Key::Left, ControllerButton::X);
  bind_key(RIGHT, Key::Right, ControllerButton::B);

  bind_direction(UI_UP, Key::Up, ControllerButton::DPadUp,
                 ControllerAxis::LeftY, false);
  bind_direction(UI_DOWN, Key::Down, ControllerButton::DPadDown,
                 ControllerAxis::LeftY, true);
  bind_direction(UI_LEFT, Key::Left, ControllerButton::DPadLeft,
                 ControllerAxis::LeftX, false);
  bind_direction(UI_RIGHT, Key::Right, ControllerButton::DPadRight,
                 ControllerAxis::LeftX, true);

  bind_key(UI_CONFIRM, Key::Return, ControllerButton::A);
  asw::input::bind_action(
      UI_CONFIRM, ControllerButtonBinding{ControllerButton::Start, ANY});

  // Not B, it is a stair key and a stray press would quit a level
  bind_key(UI_BACK, Key::Escape, ControllerButton::Back);
}

bool controls::using_controller() {
  return asw::input::get_last_device() == asw::input::InputDevice::Controller;
}

bool controls::any_controller_skip() {
  return asw::input::get_controller_button_down(ANY, ControllerButton::A) ||
         asw::input::get_controller_button_down(ANY, ControllerButton::B) ||
         asw::input::get_controller_button_down(ANY, ControllerButton::Start);
}
