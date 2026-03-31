#include "KeyManager.h"

#include <array>
#include <string>

namespace {
const std::array<std::string, 4> action_ids = {"up", "down", "left", "right"};
}

// Init
KeyManager::KeyManager(int x, int y) : x(x), y(y) {
  // Add keys
  for (int i = 0; i < 4; i++) {
    pushKey();
  }

  // Load images
  keys[0] = asw::assets::load_texture("assets/images/keys/key_up.png");
  keys[1] = asw::assets::load_texture("assets/images/keys/key_down.png");
  keys[2] = asw::assets::load_texture("assets/images/keys/key_left.png");
  keys[3] = asw::assets::load_texture("assets/images/keys/key_right.png");

  buttons[0] = asw::assets::load_texture("assets/images/keys/joy_y.png");
  buttons[1] = asw::assets::load_texture("assets/images/keys/joy_a.png");
  buttons[2] = asw::assets::load_texture("assets/images/keys/joy_x.png");
  buttons[3] = asw::assets::load_texture("assets/images/keys/joy_b.png");

  sounds[0] = asw::assets::load_sample("assets/sounds/trip.wav");
  sounds[1] = asw::assets::load_sample("assets/sounds/ping.wav");
}

// Push key
void KeyManager::pushKey() {
  const int value = asw::random::between(0, action_ids.size() - 1);
  key_queue.push_back(value);
}

// Pop key
void KeyManager::popKey() {
  key_queue.erase(key_queue.begin());
}

// Update
int KeyManager::update() {
  const bool is_any_action_pressed =
      asw::input::is_action_pressed(action_ids[0]) ||
      asw::input::is_action_pressed(action_ids[1]) ||
      asw::input::is_action_pressed(action_ids[2]) ||
      asw::input::is_action_pressed(action_ids[3]);

  // Got a correct letter
  if (!key_queue.empty() && is_any_action_pressed) {
    if (asw::input::is_action_pressed(action_ids.at(key_queue.at(0)))) {
      asw::sound::play(sounds[1]);
      popKey();
      pushKey();
      return 1;
    }

    asw::sound::play(sounds[0]);
    return -1;
  }

  return 0;
}

// Draw
void KeyManager::draw() {
  // Background
  asw::draw::rect_fill(
      asw::Quadf(x + 15, y + 75, 209 - 95, 7 + (key_queue.size() * 90)),
      asw::Color(155, 155, 155));

  // Draw keys
  for (unsigned int i = 0; i < key_queue.size(); i++) {
    const auto button_position = asw::Vec2f(x + 20, -(i * 90) + y + 350);

    if (asw::input::get_controller_count() > 0) {
      asw::draw::sprite(buttons[key_queue.at(i)], button_position);
    } else {
      asw::draw::sprite(keys[key_queue.at(i)], button_position);
    }
  }
}
