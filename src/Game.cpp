#include "Game.h"

#include <math.h>

#include "globals.h"
#include "tools.h"

#include <iostream>

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

  // Sets Fonts
  font = load_font_ex("fonts/dosis.pcx");
  dosis_26 = load_font_ex("fonts/dosis_26.pcx");

  // Keys
  screen_keys = new key_manager (20, 50);

  // Player
  player = new Player (10 * 30, Stair::location_y (10 * 30) - 90);

  // Reset variables
  parallax_scroll = 0.0;
  distance_travelled = 0.0;
  switch_flicked = false;
  distance_is_reached = false;
  Stair::final_stair_placed = false;
  Stair::locationOfFinal = 0;
  Stair::numberStairs = 0;
  scroll_speed = 0.0f;

  // Stairs (offset is 30 px)
  for (int i = SCREEN_W / 4; i < SCREEN_W; i += 30) {
    stairs.push_back (Stair(i, Stair::location_y (i), 0));
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

  // Fonts
  destroy_font (dosis_26);

  delete screen_keys;
  delete player;

  goats.clear();
  stairs.clear();

  // Stop music
  stop_sample (music);

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
      (screen_keys -> buttonDown() || screen_keys -> keyDown())) {
    start_time.Start();
  }

  // Win
  if (switch_flicked) {
    if (start_time.IsRunning()) {
      start_time.Stop();
      end_time.Start();
      levelPtr -> completed = true;
      play_sample (win, 255, 125, 1000, 0);
      stop_sample (music);
      scroll_speed = 0;
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

  // Get key triggers
  else {
    int input = screen_keys -> update();

    // Success!
    if (input == 1 && scroll_speed < max_scroll_speed) {
      scroll_speed += 0.8;
    }
    // Failure
    else if (input == -1) {
      scroll_speed /= 4;
    }

    // Slow stairs down
    if (scroll_speed > 0.01) {
      scroll_speed -= 0.02;
    }
    else {
      scroll_speed = 0;
    }
  }

  // Move
  if (!distance_is_reached) {
    distance_travelled += scroll_speed / 25;
    if (distance_travelled >= levelPtr -> distance) {
      distance_travelled = levelPtr -> distance;
      distance_is_reached = true;
    }
  }

  // When you reach destination
  if ((player -> getY() <= (Stair::locationOfFinal - player -> getHeight())) && Stair::final_stair_placed) {
    switch_flicked = true;

    for (auto s = stairs.begin(); s < stairs.end(); s++) {
      if (s -> getType() == 1) {
        s -> setType (2);
      }
    }
  }

  // Scroll background
  parallax_scroll = scroll_speed / 4;
  if (parallax_scroll < 0) {
    parallax_scroll = 1024;
  }

  // Stairs!
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s -> update (&stairs);
  }

  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s -> scroll(scroll_speed);
  }

  // Character
  player -> update(int (ceil (scroll_speed)) % 8);

  // Update goats
  for (auto g = goats.begin(); g < goats.end(); ) {
    g -> update();
    g -> fall (switch_flicked * 5);
    g -> offScreen() ? g = goats.erase(g) : ++g;
  }

  // Spawn some motherfing goats!
  if (random (0, 100) == 0) {
    float randomDistance = float (random (2, 6)) / 10;
    goats.push_back (Goat(SCREEN_W, random (0, SCREEN_H), randomDistance, randomDistance * 3));
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
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s -> draw (buffer);
  }

  // Character
  player -> draw (buffer);

  // Distance
  rectfill (buffer, 20, 20, 620, 80, makecol (0, 0, 0));
  rectfill (buffer, 24, 24, 616, 76, makecol (255, 255, 255));
  rectfill (buffer, 24, 24, 24 + (600 * (distance_travelled / levelPtr -> distance)), 76, makecol (0, 255, 0));
  textprintf_ex (buffer, font, 20, 32, makecol (0, 0, 0), -1, "%4.0f/%i", distance_travelled, levelPtr -> distance);

  // Win / Lose text
  if (switch_flicked) {
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
