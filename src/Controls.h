#pragma once

// Input actions shared by keyboard and controllers
namespace controls {

// Stair climbing keys, shown in the key queue
inline constexpr const char* UP = "up";
inline constexpr const char* DOWN = "down";
inline constexpr const char* LEFT = "left";
inline constexpr const char* RIGHT = "right";

// Menu and screen actions
inline constexpr const char* UI_UP = "ui_up";
inline constexpr const char* UI_DOWN = "ui_down";
inline constexpr const char* UI_LEFT = "ui_left";
inline constexpr const char* UI_RIGHT = "ui_right";
inline constexpr const char* UI_CONFIRM = "ui_confirm";
inline constexpr const char* UI_BACK = "ui_back";

// Bind every action, call once after asw::core::init
void bind();

// Check if the controller was the last device used
bool using_controller();

// Check if a controller button that skips a screen was pressed
bool any_controller_skip();

}  // namespace controls
