#ifndef MENU_H
#define MENU_H

#include "State.h"

#include <allegro.h>
#include <vector>

#include "Button.h"
#include "Goat.h"

class Menu : public State {
 public:
  Menu();
  ~Menu();

  virtual void update(StateEngine* engine) override;
  virtual void draw(BITMAP* buffer) override;

 private:
  // Menu/GUI
  BITMAP *title, *sky, *city;
  BITMAP *cursor, *cursor2;
  BITMAP* little_xbox_buttons;
  BITMAP* background[2];

  // Sound
  SAMPLE* NOTALLOWED;

  // Buttons
  Button start, story, options, exit;

  // Movement
  float title_y;
  float city_x;

  // Flippy switch
  bool switchFlipped;

  // Goats
  std::vector<Goat> goats;

  SAMPLE* music;
};

#endif  // MENU_H
