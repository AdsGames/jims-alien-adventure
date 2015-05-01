#ifndef GAME_H
#define GAME_H

#include "GameState.h"

#include <allegro.h>
#include <alpng.h>
#include <string>
#include <vector>

#include "fmod/fmod.h"
#include "fmod/fmod_errors.h"

#include "globals.h"
#include "tools.h"

using namespace std;

// Main game screen
class Game : public GameState
{
  private:
    // Music
    FSOUND_STREAM* mainMusic;

    // Variables
    int animationFrame;
    static volatile int timer1;
    bool gameBegin;
    int totalTime[2];
    float scroll_speed;
    float scroll_amount;

    // Images
    BITMAP* buffer;
    BITMAP* stairs;

    // Lighting effects
    COLOR_MAP light_table;
    PALLETE pal;
    bool lightingEnabled;
    BITMAP *darkness, *darkness_old, *lightBuffer, *spotlight;

    static void gameTicker();

    // FUNctions
    float location_y( int oldX);

  public:
    //Main loop functions
    Game();
    void init();
    void update();
    void draw();
    ~Game();
};

#endif
