#ifndef MENU_H
#define MENU_H

#include "GameState.h"

#include <allegro.h>
#include <loadpng.h>
#include <string>
#include <vector>

#include <logg.h>

#include "globals.h"
#include "tools.h"
#include "button.h"
#include "goat.h"

class Menu : public GameState {
  private:
    // Menu/GUI
    BITMAP *buffer;
    BITMAP *title, *sky, *city;
    BITMAP *cursor;
    BITMAP *little_xbox_buttons;
    BITMAP *background[2];

    // Sound
    SAMPLE *NOTALLOWED;

    // Buttons
    Button *start, *story, *options, *exit;

    // Movement
    float title_y;
    float city_x;

    // Flippy switch
    bool switchFlipped;

    // Goats
    vector<goat> goats;

    SAMPLE *music;
  protected:
  public:
    //Main loop functions
    Menu();
    void update();
    void draw();
    ~Menu();
};

#endif // MENU_H
