#pragma once

#include <asw/asw.h>
#include <asw/util/Timer.h>
#include <vector>

#include "../Goat.h"
#include "../KeyManager.h"
#include "../LevelData.h"
#include "../Player.h"
#include "../Stair.h"
#include "./States.h"

// Main game screen
class Game : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  // Music
  asw::Music music;

  // Fonts
  asw::Font font;
  asw::Font dosis_26;

  // Sounds
  asw::Sample win;
  asw::Sample lose;

  // Player
  Player player;

  // All stairs
  std::vector<Stair> stairs;
  std::vector<Goat> goats;

  // Level pointer for quick lookups
  Level* levelPtr;

  // Key Manager
  KeyManager screen_keys;

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
  const float max_scroll_speed = 6.0F;

  // Timers
  Timer start_time;
  Timer end_time;

  // Constants
  static constexpr float success_boost = 1.6F;
  static constexpr float failure_boost = 0.25F;
  static constexpr float scroll_speed_multiplier = 0.00125F;
  static constexpr float scroll_speed_minimum = 0.02F;
  static constexpr float parallax_speed_multiplier = 0.25F;
  static constexpr float distance_multiplier = 0.0625F;
};
