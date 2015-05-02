#ifndef MENU_H
#define MENU_H

#include "GameState.h"

#include <allegro.h>
#include <alpng.h>
#include <string>
#include <vector>

#include "fmod/fmod.h"
#include "fmod/fmod_errors.h"

#include "globals.h"
#include "tools.h"
#include "button.h"

class Menu : public GameState
{
  private:
    // Menu/GUI
    BITMAP *buffer;
    BITMAP *background, *title, *sky, *city;
    BITMAP *cursor;
    BITMAP *button_images[4][2];

    // Buttons
    Button *start, *story, *options, *exit;

    // Movement
    float title_y;
    float city_x;

    FSOUND_STREAM* music;
  protected:
  public:
    //Main loop functions
    Menu();
    void update();
    void draw();
    ~Menu();
};

#endif // MENU_H
