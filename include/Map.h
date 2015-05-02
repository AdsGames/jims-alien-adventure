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

class Map : public GameState
{
  private:
    // Map/GUI
    BITMAP *buffer;

    FSOUND_STREAM* music;
  protected:
  public:
    //Main loop functions
    Map();
    void update();
    void draw();
    ~Map();
};

#endif // MAP_H
