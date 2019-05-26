#ifndef GAME_H
#define GAME_H

#include "State.h"

#include <allegro.h>
#include <vector>

#include "stair.h"
#include "player.h"
#include "goat.h"
#include "key_manager.h"
#include "LevelData.h"

// Main game screen
class Game : public State {
  public:
    Game();
    ~Game();

    void init();
    virtual void update(StateEngine *engine) override;
    virtual void draw(BITMAP *buffer) override;

  private:
    // Music
    SAMPLE *music;

    // Variables
    int animationFrame;

    FONT *dosis_26;
    // Player
    player *player1;

    SAMPLE *win;
    SAMPLE *lose;

    // All stairs
    std::vector<stair> allStairs;
    std::vector<goat> goats;

    Level *levelPtr;

    // Key Manager
    key_manager *screen_keys;

    bool sound_played;

    // Images
    BITMAP *stair_buffer;
    BITMAP *background_sky, *background_buildings;
    BITMAP *watch;
    BITMAP *youwin;
    BITMAP *youlose;

    float background_scroll;
    float distance_travelled;

    // Timers
    static volatile int timer1;
    static volatile float climb_time;
    static volatile float time_since_win;

    static void gameTicker();
    static void gameTimer();
    static void endTimer();
};

#endif
