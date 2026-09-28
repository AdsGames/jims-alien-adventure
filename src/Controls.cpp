#include "Controls.h"

#include <array>
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

void bind_button(const std::string& name, ControllerButton button) {
  asw::input::bind_action(name, ControllerButtonBinding{button, ANY});
}

void bind_key(const std::string& name, Key key, ControllerButton button) {
  asw::input::bind_action(name, KeyBinding{key});
  bind_button(name, button);
}

void bind_direction(const std::string& name,
                    ControllerButton dpad,
                    ControllerAxis axis,
                    bool positive) {
  bind_button(name, dpad);
  asw::input::bind_action(
      name, ControllerAxisBinding{axis, ANY, STICK_THRESHOLD, positive});
}

struct Direction {
  const char* action;
  int dx;
  int dy;
};

constexpr std::array<Direction, 4> DIRECTIONS = {{
    {controls::UI_UP, 0, -1},
    {controls::UI_DOWN, 0, 1},
    {controls::UI_LEFT, -1, 0},
    {controls::UI_RIGHT, 1, 0},
}};

void move_focus(asw::ui::Context& ctx,
                const Direction& direction,
                controls::Navigation navigation) {
  if (navigation == controls::Navigation::Spatial) {
    ctx.focus.focus_dir(ctx, direction.dx, direction.dy);
  } else if (direction.dx + direction.dy > 0) {
    ctx.focus.focus_next(ctx);
  } else {
    ctx.focus.focus_prev(ctx);
  }
}
}  // namespace

void controls::bind() {
  // Face buttons match the controller key images
  bind_key(UP, Key::Up, ControllerButton::Y);
  bind_key(DOWN, Key::Down, ControllerButton::A);
  bind_key(LEFT, Key::Left, ControllerButton::X);
  bind_key(RIGHT, Key::Right, ControllerButton::B);

  bind_direction(UI_UP, ControllerButton::DPadUp, ControllerAxis::LeftY,
                 false);
  bind_direction(UI_DOWN, ControllerButton::DPadDown, ControllerAxis::LeftY,
                 true);
  bind_direction(UI_LEFT, ControllerButton::DPadLeft, ControllerAxis::LeftX,
                 false);
  bind_direction(UI_RIGHT, ControllerButton::DPadRight, ControllerAxis::LeftX,
                 true);

  bind_button(UI_CONFIRM, ControllerButton::A);
  bind_button(UI_CONFIRM, ControllerButton::Start);

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

void controls::update_ui(asw::ui::Root& ui, Navigation navigation) {
  ui.update();

  auto& ctx = ui.ctx;
  const bool controller = using_controller();

  // Controller players get a focused widget instead of the mouse cursor
  asw::input::set_cursor_visible(!controller);

  // The root shows focus for the keyboard and hides it for the mouse
  if (controller) {
    ctx.theme.show_focus = true;
  }
  const bool focus_mode = ctx.theme.show_focus;

  // asw buttons draw their hover image while focused, so they only take
  // focus while it shows. Otherwise the mouse would see a highlighted button.
  for (const auto& child : ui.root.children) {
    child->focusable = focus_mode;
  }

  // Only the focused widget highlights in focus mode, not the one under the
  // cursor. The next mouse move hovers it again.
  if (focus_mode && ctx.hover != nullptr) {
    ctx.hover->on_event(
        ctx, asw::ui::UIEvent{.type = asw::ui::UIEvent::Type::PointerLeave});
    ctx.hover = nullptr;
  }

  ui.validate();

  for (const auto& direction : DIRECTIONS) {
    if (asw::input::get_action_down(direction.action)) {
      move_focus(ctx, direction, navigation);
    }
  }

  if (asw::input::get_action_down(UI_CONFIRM)) {
    ui.dispatch_to_focused(
        asw::ui::UIEvent{.type = asw::ui::UIEvent::Type::Activate});
  }
}
