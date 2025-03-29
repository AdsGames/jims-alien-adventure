#pragma once

#include <asw/asw.h>
#include <vector>

#include "../Button.h"
#include "../Goat.h"
#include "./States.h"

class Menu : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
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

  // Buttons
  Button start, story, options, exit;

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
  static constexpr float city_speed_multiplier = 0.125F;
  static constexpr float title_speed_multiplier = 0.25F;
};
