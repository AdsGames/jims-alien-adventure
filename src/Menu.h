#ifndef MENU_H
#define MENU_H

#include "State.h"

#include <asw/asw.h>
#include <vector>

#include "Button.h"
#include "Goat.h"

class Menu : public State {
 public:
  Menu();

  virtual void update(StateEngine* engine) override;
  virtual void draw() override;

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

  asw::Sample music;
};

#endif  // MENU_H
