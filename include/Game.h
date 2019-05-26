#ifndef GAME_H
#define GAME_H

#include "State.h"

#include <allegro.h>
#include <vector>

#include "Stair.h"
#include "Player.h"
#include "Goat.h"
#include "KeyManager.h"
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
    Player *player1;

    SAMPLE *win;
    SAMPLE *lose;

    // All stairs
    std::vector<Stair> allStairs;
    std::vector<Goat> goats;

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
