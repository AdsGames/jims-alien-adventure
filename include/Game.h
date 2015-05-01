#ifndef GAME_H
#define GAME_H

#include "GameState.h"

#include <allegro.h>
#include <alpng.h>
#include <string>
#include <vector>
#include <math.h>

#include "fmod/fmod.h"
#include "fmod/fmod_errors.h"

#include "globals.h"
#include "tools.h"

#include "stair.h"
#include "player.h"
#include "key_manager.h"

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

    // Player
    player *player1;

    // Keymanager
    key_manager *screen_keys;

    // Images
    BITMAP* buffer;

    // Lighting effects
    COLOR_MAP light_table;
    PALLETE pal;
    bool lightingEnabled;
    BITMAP *darkness, *darkness_old, *lightBuffer, *spotlight;

    static void gameTicker();

  public:
    //Main loop functions
    Game();
    void init();
    void update();
    void draw();
    ~Game();
};

#endif
