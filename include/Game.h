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
#include "goat.h"

using namespace std;

// Main game screen
class Game : public GameState
{
  private:
    // Music
    FSOUND_STREAM* mainMusic;

    // Variables
    int animationFrame;
    bool gameBegin;
    int totalTime[2];

    FONT* dosis_26;
    // Player
    player *player1;

    vector<goat> goats;

    // Key Manager
    key_manager *screen_keys;

    // Images
    BITMAP* buffer, *stair_buffer;
    BITMAP* background_sky, *background_buildings;
    BITMAP* watch;

    float background_scroll;

    // Timers
    static volatile int timer1;
    static volatile float climb_time;

    static void gameTicker();
    static void gameTimer();

  public:
    //Main loop functions
    Game();
    void init();
    void update();
    void draw();
    ~Game();
};

#endif
