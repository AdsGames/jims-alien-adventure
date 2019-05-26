#include "Game.h"

#include <math.h>

#include "globals.h"
#include "tools.h"

volatile int Game::timer1 = 0;
volatile float Game::climb_time = 0;
volatile float Game::time_since_win = 0;

Game::Game() {
  // Init
  init();
}

void Game::gameTicker() {
  timer1++;
}
END_OF_FUNCTION (gameTicker)

void Game::gameTimer() {
  if (!switch_flicked) {
    climb_time += 0.1;
  }
}
END_OF_FUNCTION (gameTimer)

void Game::endTimer() {
  time_since_win += 0.1;
}
END_OF_FUNCTION (endTimer)


void Game::init() {
  // Setup for FPS system
  LOCK_VARIABLE (timer1);
  LOCK_FUNCTION (gameTicker);
  install_int_ex (gameTicker, BPS_TO_TIMER (10));

  // Timer!
  LOCK_VARIABLE (climb_time);
  LOCK_FUNCTION (gameTimer);

  // Timer!
  LOCK_VARIABLE (time_since_win);
  LOCK_FUNCTION (endTimer);

  // Load music
  music = load_ogg_ex("music/JAA-Ingame.ogg");

  // Load images
  levelPtr = LevelData::GetLevelData() -> GetLevel(levelOn);
  background_sky = load_png_ex (("images/levels/" + levelPtr -> folder + "/sky.png").c_str());
  background_buildings = load_png_ex (("images/levels/" + levelPtr -> folder + "/parallax.png").c_str());

  // Keys
  key_manager::keys[KEY_UP] = load_png_ex("images/keys/key_up.png");
  key_manager::keys[KEY_DOWN] = load_png_ex("images/keys/key_down.png");
  key_manager::keys[KEY_LEFT] = load_png_ex("images/keys/key_left.png");
  key_manager::keys[KEY_RIGHT] = load_png_ex("images/keys/key_right.png");
  key_manager::keys[0] = load_png_ex("images/keys/joy_a.png");
  key_manager::keys[3] = load_png_ex("images/keys/joy_y.png");
  key_manager::keys[2] = load_png_ex("images/keys/joy_x.png");
  key_manager::keys[1] = load_png_ex("images/keys/joy_b.png");

  // Misc
  watch = load_png_ex("images/watch.png");
  youwin = load_png_ex("images/youwin.png");
  youlose = load_png_ex("images/youlose.png");

  // Sounds
  key_manager::sounds[0] = load_sample_ex ("sounds/trip.wav");
  key_manager::sounds[1] = load_sample_ex ("sounds/ping.wav");

  win = load_sample_ex ("sounds/win.wav");
  lose = load_sample_ex ("sounds/lose.wav");

  // Other Sprites
  stair_buffer = create_bitmap (SCREEN_W, SCREEN_H);

  // Sets Fonts
  font = load_font_ex("fonts/dosis.pcx");
  dosis_26 = load_font_ex("fonts/dosis_26.pcx");

  // Keys
  screen_keys = new key_manager (20, 50);

  // Player
  player1 = new Player (10 * 30, Stair::location_y (10 * 30) - 90);

  // Reset variables
  animationFrame = 0;
  background_scroll = 0.0;
  distance_travelled = 0.0;
  switch_flicked = false;
  distance_is_reached = false;
  Stair::final_stair_placed = false;
  Stair::locationOfFinal = 0;
  Stair::numberStairs = 0;
  sound_played = false;

  timer1 = 0;
  climb_time = 0;
  time_since_win = 0;

  // Stairs (offset is 30 px)
  for (int i = SCREEN_W / 4; i < SCREEN_W; i += 30) {
    Stair newStair (i, Stair::location_y (i), 0);
    allStairs.push_back (newStair);
  }


  // Init variables
  Stair::scrollSpeed = 0;

  // Start music
  play_sample (music, 255, 128, 1000, 1);
}

// Destroy
Game::~Game() {
  // Destroy images
  destroy_bitmap (stair_buffer);
  destroy_bitmap (background_sky);
  destroy_bitmap (background_buildings);
  destroy_bitmap (watch);
  destroy_bitmap (youwin);

  // Fonts
  destroy_font (dosis_26);

  // Timers
  remove_int (gameTimer);
  remove_int (gameTicker);
  remove_int (endTimer);

  delete screen_keys;
  delete player1;

  goats.clear();
  allStairs.clear();

  // Stop music
  stop_sample (music);

  // Fade out
  highcolor_fade_out (16);
}

// Update game state
void Game::update(StateEngine *engine) {

  // Joystick input
  poll_joystick();

  // Start timer
  if ((screen_keys -> buttonDown() || screen_keys -> keyDown()) && climb_time <= 0) {
    install_int_ex (gameTimer, BPS_TO_TIMER (10));
  }

  // Add to distance until switch is flicked
  if (!switch_flicked) {
    distance_travelled += Stair::scrollSpeed / 25;
  }

  // When you reach destination
  if ((player1 -> getY() <= (Stair::locationOfFinal - player1 -> getHeight())) && Stair::final_stair_placed) {
    switch_flicked = true;

    for (unsigned int i = 0; i < allStairs.size(); i++) {
      if (allStairs.at (i).getType() == 1) {
        allStairs.at (i).setType (2);
      }
    }
  }

  // You reached distance for spawning top!
  if (distance_travelled > levelPtr -> distance && !distance_is_reached) {
    distance_is_reached = true;
  }


  // Scroll background
  background_scroll -= Stair::scrollSpeed / 4;

  if (background_scroll < 0) {
    background_scroll = 1024;
  }

  // Stairs!
  for (unsigned int i = 0; i < allStairs.size(); i ++) {
    allStairs.at (i).update (&allStairs);
  }

  for (unsigned int i = 0; i < allStairs.size(); i ++) {
    allStairs.at (i).movement();
  }

  // Character
  player1 -> update(int (timer1 * ceil (Stair::scrollSpeed)) % 8);

  // Update goats
  for (auto g = goats.begin(); g < goats.end(); ) {
    g -> update();
    g -> fall (switch_flicked * 5);
    g -> offScreen() ? g = goats.erase(g) : ++g;
  }

  // End game
  if (time_since_win >= 3.0) {
    setNextState (engine, StateEngine::STATE_MENU);
  }
  else if (switch_flicked && time_since_win <= 0) {
    install_int_ex (endTimer, BPS_TO_TIMER (10));
  }


  // Motherfing goats!
  if (random (0, 100) == 0) {
    float randomDistance = float (random (2, 6)) / 10;
    Goat newGoat (SCREEN_W, random (0, SCREEN_H), randomDistance, randomDistance * 3);
    goats.push_back (newGoat);
  }

  // Back to menu
  if (key[KEY_M]) {
    setNextState (engine, StateEngine::STATE_MENU);
  }

  if (levelPtr -> time - climb_time <= 0) {
    install_int_ex (endTimer, BPS_TO_TIMER (10));
    climb_time = levelPtr -> time;

    if (!sound_played) {
      play_sample (lose, 255, 125, 1000, 0);
      sound_played = true;
      // Stop music
      stop_sample (music);
    }
  }

  if (switch_flicked) {
    // LEVEL DIFFICULTY!
    levelPtr -> completed = true;

    if (!sound_played) {
      play_sample (win, 255, 125, 1000, 0);
      sound_played = true;
      // Stop music
      stop_sample (music);
    }
  }

  // Key manager
  screen_keys -> update();
}

// Draw game state
void Game::draw(BITMAP *buffer) {
  // Background
  rectfill (buffer, 0, 0, SCREEN_W, SCREEN_H, makecol (255, 255, 255));
  stretch_sprite (buffer, background_sky, 0, 0, SCREEN_W, SCREEN_H);
  draw_sprite (buffer, background_buildings, 0 + background_scroll, SCREEN_H - 270);
  draw_sprite (buffer, background_buildings, -1024 + background_scroll, SCREEN_H - 270);

  // Draw goats
  for (unsigned int i = 0; i < goats.size(); i++) {
    goats.at (i).draw (buffer);
  }

  // Stairs!
  rectfill (stair_buffer, 0, 0, SCREEN_W, SCREEN_H, makecol (255, 0, 255));

  for (unsigned int i = 0; i < allStairs.size(); i ++) {
    // Draw
    allStairs.at (i).draw (stair_buffer);
  }

  draw_sprite (buffer, stair_buffer, 0, 0);

  // Character
  player1 -> draw (buffer);

  // Key manager
  if (!switch_flicked) {
    screen_keys -> draw (buffer);
  }

  // Timer
  rectfill (buffer, 20, 20, 620, 80, makecol (0, 0, 0));
  rectfill (buffer, 24, 24, 616, 76, makecol (255, 255, 255));

  if (distance_is_reached) {
    rectfill (buffer, 24, 24, 616, 76, makecol (0, 255, 0));
  }

  if (!distance_is_reached) {
    rectfill (buffer, 24, 24, 24 + (600 * (distance_travelled / levelPtr -> distance)), 76, makecol (0, 255, 0));
  }


  if (!distance_is_reached) {
    textprintf_ex (buffer, font, 20, 32, makecol (0, 0, 0), -1, "%4.0f/%i", distance_travelled, levelPtr -> distance);
  }

  if (distance_is_reached) {
    textprintf_ex (buffer, font, 40, 32, makecol (0, 0, 0), -1, "%i/%i", levelPtr -> distance, levelPtr -> distance);
  }



  if (switch_flicked) {
    draw_sprite (buffer, youwin, 200, 200);
  }

  if (levelPtr -> time - climb_time <= 0) {
    draw_sprite (buffer, youlose, 200, 200);
  }

  set_alpha_blender();

  draw_trans_sprite (buffer, watch, SCREEN_W - 122, SCREEN_H - 70);

  if (levelPtr -> time - climb_time > 0) {
    textprintf_ex (buffer, dosis_26, SCREEN_W - 97, SCREEN_H - 60, makecol (255, 255, 255), -1, "%4.1f", levelPtr -> time - climb_time);
  }

  if (levelPtr -> time - climb_time <= 0) {
    textprintf_ex (buffer, dosis_26, SCREEN_W - 97, SCREEN_H - 60, makecol (255, 255, 255), -1, "0.0");
  }
}
