#pragma once

#include <asw/asw.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../Goat.h"
#include "./States.h"

class Menu : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float dt) override;

  void draw() override;

 private:
  // Add an image button to the ui
  void addButton(const std::string& name,
                 const asw::Vec2f& position,
                 std::function<void()> on_click);

  // Send a goat across the screen
  void addGoat();

  // Menu/GUI
  asw::Texture title;
  asw::Texture sky;
  asw::Texture city;
  asw::Texture cursor;
  asw::Texture cursor2;
  asw::Texture little_xbox_buttons;
  asw::Texture background[2];

  // Fonts
  asw::Font font;

  // Sound
  asw::Sample NOTALLOWED;

  // Buttons, laid out in a 2x2 grid
  std::unique_ptr<asw::ui::Root> ui;

  // Movement
  float title_y;
  float city_x;

  // Flippy switch
  bool switchFlipped;

  // Goats
  std::vector<Goat> goats;

  // Music
  asw::Music music;

  // Speed multipliers
  static constexpr float city_speed_multiplier = 125.0F;
  static constexpr float title_speed_multiplier = 250.0F;
};
