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
#include "Timer.h"

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

    // Fonts
    FONT *dosis_26;

    // Sounds
    SAMPLE *win, *lose;

    // Player
    Player *player;

    // All stairs
    std::vector<Stair> stairs;
    std::vector<Goat> goats;

    // Level pointer for quick lookups
    Level *levelPtr;

    // Key Manager
    key_manager *screen_keys;

    // Images
    BITMAP *background, *parallax;
    BITMAP *watch;
    BITMAP *youwin, *youlose;

    float parallax_scroll;
    float distance_travelled;
    float scroll_speed;
    const float max_scroll_speed = 6.0f;

    // Timers
    Timer start_time;
    Timer end_time;
};

#endif
