#include "./Menu.h"

#include <algorithm>

#include "../tools.h"

void Menu::init() {
  // Load music
  music = asw::assets::loadMusic("assets/music/JAA-Theme.ogg");

  // Load sound
  NOTALLOWED = asw::assets::loadSample("assets/sounds/goat.wav");

  // Load images
  background[0] = asw::assets::loadTexture("assets/images/menu/menu.png");
  background[1] = asw::assets::loadTexture("assets/images/menu/menu_2.png");

  title = asw::assets::loadTexture("assets/images/menu/title.png");
  sky = asw::assets::loadTexture(
      "assets/images/levels/statue_of_liberty/sky.png");
  city = asw::assets::loadTexture(
      "assets/images/levels/statue_of_liberty/parallax.png");
  cursor = asw::assets::loadTexture("assets/images/menu/cursor1.png");
  cursor2 = asw::assets::loadTexture("assets/images/menu/cursor2.png");

  little_xbox_buttons =
      asw::assets::loadTexture("assets/images/menu/angle_buttons.png");

  // Sets Font
  font = asw::assets::loadFont("assets/fonts/dosis.ttf", 12);

  // Variable set
  title_y = -(asw::util::getTextureSize(title).y + 20);
  city_x = 0;
  switchFlipped = false;

  // Buttons
  start = Button(30, 190);
  start.setImages("assets/images/menu/button_play.png",
                  "assets/images/menu/button_pushed_play.png");

  story = Button(195, 190);
  story.setImages("assets/images/menu/button_story.png",
                  "assets/images/menu/button_pushed_story.png");

  options = Button(30, 300);
  options.setImages("assets/images/menu/button_options.png",
                    "assets/images/menu/button_pushed_options.png");

  exit = Button(195, 300);
  exit.setImages("assets/images/menu/button_exit.png",
                 "assets/images/menu/button_pushed_exit.png");

  asw::sound::playMusic(music, 255);
}

void Menu::update(float deltaTime) {
  Scene::update(deltaTime);

  // Drop title
  if (title_y <= 20.0F) {
    title_y += ((20.0F - title_y) / 80.0F) * title_speed_multiplier * deltaTime;
  } else {
    title_y = 20.0F;
  }

  // Move city
  auto citySize = asw::util::getTextureSize(city);
  if (city_x < -citySize.x) {
    city_x = city_x + citySize.x;
  } else {
    city_x -= city_speed_multiplier * deltaTime;
  }

  // Buttons
  if (start.clicked()) {
    sceneManager.setNextScene(States::Map);
  }

  if (story.clicked()) {
    sceneManager.setNextScene(States::Story);
  }

  if (exit.clicked()) {
    asw::core::exit = true;
  }

  if (options.clicked()) {
    asw::sound::play(NOTALLOWED, 255, 125, 0);
  }

  // Motherfing goats!
  if (asw::random::between(0, 80) == 0 || options.clicked()) {
    goats.emplace_back(
        asw::display::getLogicalSize().x,
        asw::random::between(0, asw::display::getLogicalSize().y),
        asw::random::between(5.0F, 60.0F) / 100.0f);
    std::sort(goats.begin(), goats.end());
  }

  // Update goats
  for (auto g = goats.begin(); g < goats.end();) {
    g->update(deltaTime);
    g->setFalling(switchFlipped);
    g->offScreen() ? g = goats.erase(g) : ++g;
  }

  // Flip switch
  if (asw::input::wasButtonPressed(asw::input::MouseButton::LEFT)) {
    if ((!switchFlipped &&
         collision(595, 607, asw::input::mouse.x, asw::input::mouse.x, 236, 248,
                   asw::input::mouse.y, asw::input::mouse.y)) ||
        (switchFlipped &&
         collision(579, 591, asw::input::mouse.x, asw::input::mouse.x, 235, 247,
                   asw::input::mouse.y, asw::input::mouse.y))) {
      switchFlipped = !switchFlipped;
    }
  }

  // Cursor
  if (start.hover() || story.hover() || options.hover() || exit.hover()) {
    asw::input::setCursor(asw::input::CursorId::POINTER);
  } else {
    asw::input::setCursor(asw::input::CursorId::DEFAULT);
  }
}

void Menu::draw() {
  // Sky
  asw::draw::stretchSprite(
      sky, asw::Quad<float>(0, 0, asw::display::getLogicalSize().x,
                            asw::display::getLogicalSize().y));

  // City scroll
  auto citySize = asw::util::getTextureSize(city);
  asw::draw::sprite(
      city,
      asw::Vec2<float>(city_x, asw::display::getLogicalSize().y - citySize.y));
  asw::draw::sprite(
      city, asw::Vec2<float>(city_x + citySize.x,
                             asw::display::getLogicalSize().y - citySize.y));

  // Draw goats
  for (auto g = goats.begin(); g < goats.end(); ++g) {
    g->draw();
  }

  // Stairs
  asw::draw::sprite(background[switchFlipped], asw::Vec2<float>(0, 0));

  // Title
  asw::draw::sprite(title, asw::Vec2<float>(20, title_y));

  // Buttons
  start.draw();
  story.draw();
  options.draw();
  exit.draw();
}
