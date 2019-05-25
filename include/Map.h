#ifndef MAP_H
#define MAP_H

#include "GameState.h"

#include <allegro.h>
#include <loadpng.h>
#include <string>
#include <vector>

#include <logg.h>

#include "globals.h"
#include "tools.h"
#include "location.h"

class Map : public GameState {
  private:
    // Map/GUI
    BITMAP *buffer;
    BITMAP *map_image;
    BITMAP *cursor;

    SAMPLE *music;

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
