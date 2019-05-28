#include "Game.h"

#include <math.h>

#include "globals.h"
#include "tools.h"

#include <algorithm>

Game::Game() {
  init();
}


void Game::init() {
  // Load music
  music = load_ogg_ex("music/JAA-Ingame.ogg");

  // Load images
  levelPtr = LevelData::GetLevelData() -> GetLevel(levelOn);
  background = load_png_ex (("images/levels/" + levelPtr -> folder + "/sky.png").c_str());
  parallax = load_png_ex (("images/levels/" + levelPtr -> folder + "/parallax.png").c_str());

  // Misc
  watch = load_png_ex("images/watch.png");
  youwin = load_png_ex("images/youwin.png");
  youlose = load_png_ex("images/youlose.png");

  // Sounds
  win = load_sample_ex ("sounds/win.wav");
  lose = load_sample_ex ("sounds/lose.wav");

  // Stair buffer
  stair_buffer = create_bitmap (SCREEN_W, SCREEN_H);

  // Sets Fonts
  font = load_font_ex("fonts/dosis.pcx");
  dosis_26 = load_font_ex("fonts/dosis_26.pcx");

  // Keys
  screen_keys = new KeyManager (20, 50);

  // Player
  player = new Player (300, 300);

  // Reset variables
  parallax_scroll = 0.0;
  distance_travelled = 0.0;
  distance_is_reached = false;
  scroll_speed = 0.0f;

  // Stairs (offset is 30 px)
  for (int i = 0; i < SCREEN_W; i += 30) {
    stairs.push_back (Stair(i));
  }

  // Start music
  play_sample (music, 255, 128, 1000, 1);
}

// Destroy
Game::~Game() {
  // Destroy images
  destroy_bitmap (background);
  destroy_bitmap (parallax);
  destroy_bitmap (watch);
  destroy_bitmap (youwin);
  destroy_bitmap (youlose);
  destroy_bitmap (stair_buffer);

  // Fonts
  destroy_font (dosis_26);

  delete screen_keys;
  delete player;

  goats.clear();
  stairs.clear();

  // Stop music
  destroy_sample (music);
  destroy_sample (win);
  destroy_sample (lose);

  // Fade out
  highcolor_fade_out (16);
}

// Update game state
void Game::update(StateEngine *engine) {
  // Joystick input
  poll_joystick();

  // Back to menu if M or win/lose
  if(key[KEY_M] || end_time.GetElapsedTime<seconds>() >= 3) {
    setNextState (engine, StateEngine::STATE_MENU);
  }

  // Start timer
  if (!start_time.IsRunning() &&
       start_time.GetElapsedTime<seconds>() == 0 &&
      (button_down() || key_down())) {
    start_time.Start();
  }

  // Win
  if (distance_is_reached) {
    if (start_time.IsRunning()) {
      start_time.Stop();
      end_time.Start();
      levelPtr -> completed = true;
      play_sample (win, 255, 125, 1000, 0);
      stop_sample (music);
    }
  }

  // Lose
  else if (start_time.GetElapsedTime<seconds>() >= levelPtr -> time) {
    if (start_time.IsRunning()) {
      start_time.Stop();
      end_time.Start();
      play_sample (lose, 255, 125, 1000, 0);
      stop_sample (music);
      scroll_speed = 0;
    }
  }

  // Move
  else {
    distance_travelled += scroll_speed;
    if (distance_travelled > levelPtr -> distance) {
      distance_travelled = levelPtr -> distance;
      distance_is_reached = true;
      scroll_speed = 0;
    }

    // Get key triggers
    int input = screen_keys -> update();

    // Success!
    if (input == 1 && scroll_speed < max_scroll_speed) {
      scroll_speed += 0.8;
    }
    // Failure
    else if (input == -1) {
      scroll_speed /= 4.0f;
    }
  }

  // Slow stairs down
  if (scroll_speed > 0.02f) {
    scroll_speed -= 0.02f;
  }
  else {
    scroll_speed = 0;
  }

  // Scroll background
  parallax_scroll = scroll_speed / 4.0f;
  if (parallax_scroll < 0.0f) {
    parallax_scroll = 1024.0f;
  }

  // Stairs!
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s -> update (levelPtr -> distance - distance_travelled, scroll_speed);
  }

  // Character
  player -> update(int (ceil (start_time.GetElapsedTime<milliseconds>() / 100.0f * scroll_speed)) % 8);

  // Update goats
  for (auto g = goats.begin(); g < goats.end(); ) {
    g -> update();
    g -> fall (distance_is_reached * 5);
    g -> offScreen() ? g = goats.erase(g) : ++g;
  }

  // Spawn some motherfing goats!
  if (random (0, 100) == 0) {
    goats.push_back (Goat(SCREEN_W, random (0, SCREEN_H), float (random (5, 60)) / 100.0f));
    std::sort(goats.begin(), goats.end());
  }
}

// Draw game state
void Game::draw(BITMAP *buffer) {
  // Background
  clear_to_color(buffer, 0x000000);
  stretch_sprite (buffer, background, 0, 0, SCREEN_W, SCREEN_H);

  // Paralax
  draw_sprite (buffer, parallax, 0 + parallax_scroll, SCREEN_H - 270);
  draw_sprite (buffer, parallax, -1024 + parallax_scroll, SCREEN_H - 270);

  // Draw goats
  for (auto g = goats.begin(); g < goats.end(); g++) {
    g -> draw (buffer);
  }

  // Stairs!
  clear_to_color(stair_buffer, 0xFF00FF);
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s -> draw (stair_buffer);
  }
  draw_sprite(buffer, stair_buffer, 0, 0);

  // Character
  player -> draw (buffer);

  // Distance
  rectfill (buffer, 20, 20, 620, 80, makecol (0, 0, 0));
  rectfill (buffer, 24, 24, 616, 76, makecol (255, 255, 255));
  rectfill (buffer, 24, 24, 24 + (592 * (distance_travelled / levelPtr -> distance)), 76, makecol (0, 255, 0));
  textprintf_ex (buffer, font, 30, 32, makecol (0, 0, 0), -1, "%4.0f/%i", distance_travelled, levelPtr -> distance);

  // Win / Lose text
  if (distance_is_reached) {
    draw_sprite (buffer, youwin, 200, 200);
  }
  else if (start_time.GetElapsedTime<seconds>() >= levelPtr -> time) {
    draw_sprite (buffer, youlose, 200, 200);
  }
  else {
    screen_keys -> draw (buffer);
  }

  // Timer
  set_alpha_blender();
  draw_trans_sprite (buffer, watch, SCREEN_W - 122, SCREEN_H - 70);
  textprintf_right_ex (buffer, dosis_26, SCREEN_W - 30, SCREEN_H - 60, makecol (255, 255, 255), -1, "%4.1f", start_time.GetElapsedTime<milliseconds>() / 1000);
}
