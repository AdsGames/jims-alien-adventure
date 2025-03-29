#include "./Game.h"

#include <algorithm>
#include <cmath>

#include "../globals.h"
#include "../tools.h"

void Game::init() {
  // Load music
  music = asw::assets::loadMusic("assets/music/JAA-Ingame.ogg");

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

  // Sets Fonts
  font = asw::assets::loadFont("assets/fonts/dosis.ttf", 28);
  dosis_26 = asw::assets::loadFont("assets/fonts/dosis.ttf", 26);

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
  for (int i = 0; i < asw::display::getLogicalSize().x; i += 30) {
    stairs.emplace_back(i);
  }

  // Reset timers
  start_time = Timer();
  end_time = Timer();

  // Start music
  asw::sound::playMusic(music, 255);
}

// Update game state
void Game::update(float deltaTime) {
  Scene::update(deltaTime);

  // Fix timestep
  auto distance_covered = scroll_speed * deltaTime * distance_multiplier;

  // Back to menu if M or win/lose
  if (asw::input::wasKeyPressed(asw::input::Key::ESCAPE) ||
      end_time.getElapsedTime<std::chrono::seconds>() >= 3) {
    sceneManager.setNextScene(States::Menu);
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
    }
  }

  // Lose
  else if (start_time.getElapsedTime<std::chrono::seconds>() >=
           levelPtr->time) {
    if (start_time.isRunning()) {
      start_time.stop();
      end_time.start();
      asw::sound::play(lose, 255, 125, 0);
      scroll_speed = 0;
    }
  }

  // Move
  else {
    distance_travelled += distance_covered;
    if (distance_travelled > levelPtr->distance) {
      distance_travelled = levelPtr->distance;
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
    scroll_speed -= scroll_speed_multiplier * deltaTime;
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
    s->update(levelPtr->distance - distance_travelled, distance_covered);
  }

  // Character
  player.update(int(std::ceil(distance_travelled / 10.0F)) % 8);

  // Update goats
  for (auto g = goats.begin(); g < goats.end();) {
    g->update(deltaTime);
    g->setFalling(distance_is_reached);
    g->offScreen() ? g = goats.erase(g) : ++g;
  }

  // Spawn some motherfing goats!
  if (asw::random::between(0, 100) == 0) {
    goats.emplace_back(
        asw::display::getLogicalSize().x,
        asw::random::between(0, asw::display::getLogicalSize().y),
        asw::random::between(5.0F, 60.0F) / 100.0F);
    std::sort(goats.begin(), goats.end());
  }
}

// Draw game state
void Game::draw() {
  // Background
  asw::draw::stretchSprite(
      background, asw::Quad<float>(0, 0, asw::display::getLogicalSize().x,
                                   asw::display::getLogicalSize().y));

  // Paralax
  asw::draw::sprite(parallax,
                    asw::Vec2<float>(0 + parallax_scroll,
                                     asw::display::getLogicalSize().y - 270));
  asw::draw::sprite(parallax,
                    asw::Vec2<float>(-1024 + parallax_scroll,
                                     asw::display::getLogicalSize().y - 270));

  // Draw goats
  for (auto g = goats.begin(); g < goats.end(); g++) {
    g->draw();
  }

  // Stairs!
  for (auto s = stairs.begin(); s < stairs.end(); s++) {
    s->draw();
  }

  // Character
  player.draw();

  // Distance
  asw::draw::rectFill(asw::Quad<float>(20, 20, 600, 60),
                      asw::util::makeColor(0, 0, 0));
  asw::draw::rectFill(asw::Quad<float>(24, 24, 592, 52),
                      asw::util::makeColor(255, 255, 255));
  asw::draw::rectFill(
      asw::Quad<float>(24, 24, 592 * (distance_travelled / levelPtr->distance),
                       52),
      asw::util::makeColor(0, 255, 0));

  asw::draw::text(
      font, string_format("%4.0f/%d", distance_travelled, levelPtr->distance),
      asw::Vec2<float>(30, 32), asw::util::makeColor(0, 0, 0));

  // Win / Lose text
  if (distance_is_reached) {
    asw::draw::sprite(youwin, asw::Vec2<float>(200, 200));
  } else if (start_time.getElapsedTime<std::chrono::seconds>() >=
             levelPtr->time) {
    asw::draw::sprite(youlose, asw::Vec2<float>(200, 200));
  } else {
    screen_keys.draw();
  }

  // Timer
  auto timeElapsed =
      start_time.getElapsedTime<std::chrono::milliseconds>() / 1000.0;
  asw::draw::sprite(watch, asw::Vec2<float>(asw::display::getLogicalSize().x,
                                            asw::display::getLogicalSize().y) -
                               asw::Vec2<float>(122, 70));
  asw::draw::textRight(dosis_26, string_format("%4.1f", timeElapsed),
                       asw::Vec2<float>(asw::display::getLogicalSize().x,
                                        asw::display::getLogicalSize().y) -
                           asw::Vec2<float>(30, 60),
                       asw::util::makeColor(255, 255, 255));
}
