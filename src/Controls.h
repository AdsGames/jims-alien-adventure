#pragma once

#include <asw/asw.h>

// Input actions shared by keyboard and controllers
namespace controls {

// Stair climbing keys, shown in the key queue
inline constexpr const char* UP = "up";
inline constexpr const char* DOWN = "down";
inline constexpr const char* LEFT = "left";
inline constexpr const char* RIGHT = "right";

// Menu and screen actions. Arrow keys and Return are handled by the asw ui
// root, so the ui directions and confirm are controller only
inline constexpr const char* UI_UP = "ui_up";
inline constexpr const char* UI_DOWN = "ui_down";
inline constexpr const char* UI_LEFT = "ui_left";
inline constexpr const char* UI_RIGHT = "ui_right";
inline constexpr const char* UI_CONFIRM = "ui_confirm";
inline constexpr const char* UI_BACK = "ui_back";

// How controller directions move focus between widgets
enum class Navigation {
  // To the nearest widget in that direction
  Spatial,
  // Right and down to the next widget, left and up to the previous, wrapping
  Cycle,
};

// Bind every action, call once after asw::core::init
void bind();

// Check if the controller was the last device used
bool using_controller();

// Check if a controller button that skips a screen was pressed
bool any_controller_skip();

// Update a ui root, and move focus or activate widgets with a controller. The
// root already handles the mouse and keyboard. Focus only shows for the
// keyboard and controllers, and the cursor hides while using a controller.
void update_ui(asw::ui::Root& ui, Navigation navigation = Navigation::Spatial);

}  // namespace controls
