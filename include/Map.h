#ifndef MAP_H
#define MAP_H

#include "GameState.h"

#include <allegro.h>
#include <alpng.h>
#include <string>
#include <vector>

#include "fmod/fmod.h"
#include "fmod/fmod_errors.h"

#include "globals.h"
#include "tools.h"
#include "location.h"

class Map : public GameState
{
  private:
    // Map/GUI
    BITMAP *buffer;
    BITMAP *map_image;
    BITMAP *cursor;

    FSOUND_STREAM *music;

    int cursor_x, cursor_y;
    int mickeyx;
    int mickeyy;

    vector<location> mapLocations;
  protected:
  public:
    //Main loop functions
    Map();
    void update();
    void draw();
    ~Map();
};

#endif // MAP_H
