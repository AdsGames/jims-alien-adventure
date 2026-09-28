#include "./Game.h"

#include <algorithm>
#include <cmath>

#include "../globals.h"
#include "../tools.h"

void Game::init() {
  // Load music
  music = asw::assets::load_music("assets/music/JAA-Ingame.ogg");

  // Load images
  level_data = LevelData("assets/levels.json");

  auto level_opt = level_data.GetLevel(levelOn);
  if (!level_opt.has_value()) {
    asw::util::abort_on_error("Could not load level " +
                              std::to_string(levelOn));
  }
  current_level = level_opt.value();

  background = asw::assets::load_texture("assets/images/levels/" +
                                         current_level.folder + "/sky.png");
  parallax = asw::assets::load_texture("assets/images/levels/" +
                                       current_level.folder + "/parallax.png");

  // Misc
  watch = asw::assets::load_texture("assets/images/watch.png");
  youwin = asw::assets::load_texture("assets/images/youwin.png");
  youlose = asw::assets::load_texture("assets/images/youlose.png");

  // Sounds
  win = asw::assets::load_sample("assets/sounds/win.wav");
  lose = asw::assets::load_sample("assets/sounds/lose.wav");

  // Sets Fonts
  font = asw::assets::load_font("assets/fonts/dosis.ttf", 28);
  dosis_26 = asw::assets::load_font("assets/fonts/dosis.ttf", 26);

  // Keys
  screen_keys = KeyManager(20, 50);

  // Player
  player = Player(300, 300);

  // Reset variables
  parallax_scroll = 0.0F;
  distance_travelled = 0.0F;
  distance_is_reached = false;
  scroll_speed = 0.0F;
  distance_is_reached = false;
  Stair::last_stair_placed = false;

  // Stairs (offset is 30 px)
  stairs.clear();
  for (int i = 0; i < asw::display::get_logical_size().x; i += 30) {
    stairs.emplace_back(i, current_level.folder);
  }

  // Reset timers
  start_time = 0.0F;
  end_time = 0.0F;

  // Start music
  asw::sound::play_music(music);
}

// Update game state
void Game::update(float dt) {
  Scene::update(dt);

  // Fix timestep
  auto distance_covered = scroll_speed * dt * distance_multiplier;

  // Back to menu if M or win/lose
  if (asw::input::get_key_down(asw::input::Key::Escape) || end_time >= 3.0F) {
    manager.set_next_scene(States::Menu);
  }

  // Win
  if (distance_is_reached) {
    if (end_time == 0.0F) {
      current_level.completed = true;
      level_data.Save("assets/levels.json");
      asw::sound::play(win);
    }

    end_time += dt;
  }

  // Lose
  else if (start_time >= current_level.time) {
    if (end_time == 0.0F) {
      asw::sound::play(lose);
      scroll_speed = 0;
    }

    end_time += dt;
  }

  // Move
  else {
    start_time += dt;

    distance_travelled += distance_covered;
    if (distance_travelled > current_level.distance) {
      distance_travelled = current_level.distance;
      distance_is_reached = true;
      scroll_speed = 0;
    }

    // Get key triggers
    int input = screen_keys.update();

    // Success!
    if (input == 1 && scroll_speed < max_scroll_speed) {
      scroll_speed += success_boost;
    }
    // Failure
    else if (input == -1) {
      scroll_speed *= failure_boost;
    }
  }

  // Slow stairs down
  if (scroll_speed > scroll_speed_minimum) {
    scroll_speed -= scroll_speed_multiplier * dt;
  } else {
    scroll_speed = 0.0F;
  }

  // Scroll background
  parallax_scroll -= distance_covered * parallax_speed_multiplier;
  if (parallax_scroll < 0.0F) {
    parallax_scroll = 1024.0F;
  }

  // Stairs!
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s->update(current_level.distance - distance_travelled, distance_covered);
  }

  // Character
  player.update(int(std::ceil(distance_travelled / 10.0F)) % 8);

  // Update goats
  for (auto g = goats.begin(); g < goats.end();) {
    g->update(dt);
    g->setFalling(distance_is_reached);
    g->offScreen() ? g = goats.erase(g) : ++g;
  }

  // Spawn some motherfing goats!
  if (asw::random::between(0, 100) == 0) {
    const auto logical_size = asw::display::get_logical_size();

    goats.emplace_back(logical_size.x, asw::random::between(0, logical_size.y),
                       asw::random::between(5.0F, 60.0F) / 100.0F);
    std::sort(goats.begin(), goats.end());
  }
}

// Draw game state
void Game::draw() {
  const auto logical_size = asw::display::get_logical_size();

  // Background
  asw::draw::stretch_sprite(background,
                            asw::Quadf(0, 0, logical_size.x, logical_size.y));

  // Parallax
  asw::draw::sprite(parallax,
                    asw::Vec2f(0 + parallax_scroll, logical_size.y - 270));
  asw::draw::sprite(parallax,
                    asw::Vec2f(-1024 + parallax_scroll, logical_size.y - 270));

  // Draw goats
  for (const auto& g : goats) {
    g.draw();
  }

  // Stairs!
  for (const auto& s : stairs) {
    s.draw();
  }

  // Character
  player.draw();

  // Distance
  asw::draw::rect_fill(asw::Quadf(20, 20, 600, 60), asw::Color(0, 0, 0));
  asw::draw::rect_fill(asw::Quadf(24, 24, 592, 52), asw::Color(255, 255, 255));
  asw::draw::rect_fill(
      asw::Quadf(24, 24, 592 * (distance_travelled / current_level.distance),
                 52),
      asw::Color(0, 255, 0));

  asw::draw::text(
      font,
      string_format("%4.0f/%d", distance_travelled, current_level.distance),
      asw::Vec2f(30, 32), asw::Color(0, 0, 0));

  // Win / Lose text
  if (distance_is_reached) {
    asw::draw::sprite(youwin, asw::Vec2f(200, 200));
  } else if (start_time >= current_level.time) {
    asw::draw::sprite(youlose, asw::Vec2f(200, 200));
  } else {
    screen_keys.draw();
  }

  // Timer
  asw::draw::sprite(
      watch, asw::Vec2f(logical_size.x, logical_size.y) - asw::Vec2f(122, 70));
  asw::draw::text(
      dosis_26, string_format("%4.1f", start_time),
      asw::Vec2f(logical_size.x, logical_size.y) - asw::Vec2f(30, 60),
      asw::Color(255, 255, 255), asw::TextJustify::Right);
}
