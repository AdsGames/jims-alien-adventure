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
  music = asw::assets::loadSample("assets/music/JAA-Ingame.ogg");

  // Load images
  levelPtr = LevelData::GetLevelData()->GetLevel(levelOn);
  background = asw::assets::loadTexture("assets/images/levels/" +
                                        levelPtr->folder + "/sky.png");
  parallax = asw::assets::loadTexture("assets/images/levels/" +
                                      levelPtr->folder + "/parallax.png");

  // Misc
  watch = asw::assets::loadTexture("assets/images/watch.png");
  youwin = asw::assets::loadTexture("assets/images/youwin.png");
  youlose = asw::assets::loadTexture("assets/images/youlose.png");

  // Sounds
  win = asw::assets::loadSample("assets/sounds/win.wav");
  lose = asw::assets::loadSample("assets/sounds/lose.wav");

  // Stair buffer
  stair_buffer = asw::assets::createTexture(asw::display::getSize().x,
                                            asw::display::getSize().y);

  // Sets Fonts
  font = asw::assets::loadFont("assets/fonts/dosis.ttf", 28);
  dosis_26 = asw::assets::loadFont("assets/fonts/dosis.ttf", 26);

  // Keys
  screen_keys = new KeyManager(20, 50);

  // Player
  player = new Player(300, 300);

  // Reset variables
  parallax_scroll = 0.0;
  distance_travelled = 0.0;
  distance_is_reached = false;
  scroll_speed = 0.0f;

  // Stairs (offset is 30 px)
  for (int i = 0; i < asw::display::getSize().x; i += 30) {
    stairs.push_back(Stair(i));
  }

  // Start music
  asw::sound::play(music, 255, 128, 1);
}

// Update game state
void Game::update(StateEngine* engine) {
  // Back to menu if M or win/lose
  if (asw::input::keyboard.down[SDL_SCANCODE_M] ||
      end_time.getElapsedTime<std::chrono::seconds>() >= 3) {
    setNextState(engine, StateEngine::STATE_MENU);
  }

  // Start timer
  if (!start_time.isRunning() &&
      start_time.getElapsedTime<std::chrono::seconds>() == 0 &&
      asw::input::keyboard.anyPressed) {
    start_time.start();
  }

  // Win
  if (distance_is_reached) {
    if (start_time.isRunning()) {
      start_time.stop();
      end_time.start();
      levelPtr->completed = true;
      asw::sound::play(win, 255, 125, 0);
      // stop_sample(music);
    }
  }

  // Lose
  else if (start_time.getElapsedTime<std::chrono::seconds>() >=
           levelPtr->time) {
    if (start_time.isRunning()) {
      start_time.stop();
      end_time.start();
      asw::sound::play(lose, 255, 125, 0);
      // stop_sample(music);
      scroll_speed = 0;
    }
  }

  // Move
  else {
    distance_travelled += scroll_speed;

    if (distance_travelled > levelPtr->distance) {
      distance_travelled = levelPtr->distance;
      distance_is_reached = true;
      scroll_speed = 0;
    }

    // Get key triggers
    int input = screen_keys->update();

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
  } else {
    scroll_speed = 0;
  }

  // Scroll background
  parallax_scroll = scroll_speed / 4.0f;

  if (parallax_scroll < 0.0f) {
    parallax_scroll = 1024.0f;
  }

  // Stairs!
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s->update(levelPtr->distance - distance_travelled, scroll_speed);
  }

  // Character
  player->update(
      int(ceil(start_time.getElapsedTime<std::chrono::milliseconds>() / 100.0f *
               scroll_speed)) %
      8);

  // Update goats
  for (auto g = goats.begin(); g < goats.end();) {
    g->update();
    g->fall(distance_is_reached * 5);
    g->offScreen() ? g = goats.erase(g) : ++g;
  }

  // Spawn some motherfing goats!
  if (random(0, 100) == 0) {
    goats.push_back(Goat(asw::display::getSize().x,
                         random(0, asw::display::getSize().y),
                         float(random(5, 60)) / 100.0f));
    std::sort(goats.begin(), goats.end());
  }
}

// Draw game state
void Game::draw() {
  // Background
  asw::draw::stretchSprite(background, 0, 0, asw::display::getSize().x,
                           asw::display::getSize().y);

  // Paralax
  asw::draw::sprite(parallax, 0 + parallax_scroll,
                    asw::display::getSize().y - 270);
  asw::draw::sprite(parallax, -1024 + parallax_scroll,
                    asw::display::getSize().y - 270);

  // Draw goats
  for (auto g = goats.begin(); g < goats.end(); g++) {
    g->draw();
  }

  // Stairs!
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s->draw();
  }

  // Character
  player->draw();

  // Distance
  asw::draw::rectFill(20, 20, 600, 60, asw::util::makeColor(0, 0, 0));
  asw::draw::rectFill(24, 24, 592, 52, asw::util::makeColor(255, 255, 255));
  asw::draw::rectFill(24, 24, 592 * (distance_travelled / levelPtr->distance),
                      52, asw::util::makeColor(0, 255, 0));
  asw::draw::text(
      font, string_format("%4.0f/%d", distance_travelled, levelPtr->distance),
      30, 32, asw::util::makeColor(0, 0, 0));

  // Win / Lose text
  if (distance_is_reached) {
    asw::draw::sprite(youwin, 200, 200);
  } else if (start_time.getElapsedTime<std::chrono::seconds>() >=
             levelPtr->time) {
    asw::draw::sprite(youlose, 200, 200);
  } else {
    screen_keys->draw();
  }

  // Timer
  auto timeElapsed =
      start_time.getElapsedTime<std::chrono::milliseconds>() / 1000.0;
  asw::draw::sprite(watch, asw::display::getSize().x - 122,
                    asw::display::getSize().y - 70);
  asw::draw::textRight(dosis_26, string_format("%4.1f", timeElapsed),
                       asw::display::getSize().x - 30,
                       asw::display::getSize().y - 60,
                       asw::util::makeColor(255, 255, 255));
}
