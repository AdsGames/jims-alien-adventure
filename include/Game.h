#ifndef GAME_H
#define GAME_H

#include "GameState.h"

#include <logg.h>

#include <allegro.h>
#include <loadpng.h>
#include <string>
#include <vector>
#include <math.h>

#include "globals.h"
#include "tools.h"

#include "stair.h"
#include "player.h"
#include "key_manager.h"
#include "goat.h"

using namespace std;

// Main game screen
class Game : public GameState {
  private:
    // Music
    SAMPLE *mainMusic;

    // Variables
    int animationFrame;

    FONT *dosis_26;
    // Player
    player *player1;

    SAMPLE *win;
    SAMPLE *lose;

    // All stairs
    vector<stair> allStairs;
    vector<goat> goats;

    // Key Manager
    key_manager *screen_keys;

    bool sound_played;
    // Images
    BITMAP *buffer, *stair_buffer;
    BITMAP *background_sky, *background_buildings;
    BITMAP *watch;
    BITMAP *youwin;
    BITMAP *youlose;

    float background_scroll;
    float time_to_complete;

    // Timers
    static volatile int timer1;
    static volatile float climb_time;
    static volatile float time_since_win;

    static void gameTicker();
    static void gameTimer();
    static void endTimer();

  public:
    //Main loop functions
    Game();
    void init();
    void update();
    void draw();
    ~Game();
};

#endif
