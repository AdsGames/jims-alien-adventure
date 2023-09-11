#ifndef GAME_H
#define GAME_H

#include "State.h"

#include <asw/asw.h>
#include <asw/util/Timer.h>
#include <vector>

#include "Goat.h"
#include "KeyManager.h"
#include "LevelData.h"
#include "Player.h"
#include "Stair.h"

// Main game screen
class Game : public State {
 public:
  Game();

  void init();
  virtual void update(StateEngine* engine) override;
  virtual void draw() override;

 private:
  // Music
  asw::Sample music;

  // Fonts
  asw::Font font;
  asw::Font dosis_26;

  // Sounds
  asw::Sample win;
  asw::Sample lose;

  // Player
  Player* player;

  // All stairs
  std::vector<Stair> stairs;
  std::vector<Goat> goats;

  // Level pointer for quick lookups
  Level* levelPtr;

  // Key Manager
  KeyManager* screen_keys;

  // Images
  asw::Texture background;
  asw::Texture parallax;
  asw::Texture watch;
  asw::Texture youwin;
  asw::Texture youlose;
  asw::Texture stair_buffer;

  float parallax_scroll;
  float distance_travelled;
  float scroll_speed;
  bool distance_is_reached;
  const float max_scroll_speed = 6.0f;

  // Timers
  Timer start_time;
  Timer end_time;
};

#endif
