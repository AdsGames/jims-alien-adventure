#include "Menu.h"

#include "tools.h"

#include <algorithm>

Menu::Menu() {
  // Load music
  music = asw::assets::loadSample("assets/music/JAA-Theme.ogg");

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
  start.SetImages("assets/images/menu/button_play.png",
                  "assets/images/menu/button_pushed_play.png");

  story = Button(195, 190);
  story.SetImages("assets/images/menu/button_story.png",
                  "assets/images/menu/button_pushed_story.png");

  options = Button(30, 300);
  options.SetImages("assets/images/menu/button_options.png",
                    "assets/images/menu/button_pushed_options.png");

  exit = Button(195, 300);
  exit.SetImages("assets/images/menu/button_exit.png",
                 "assets/images/menu/button_pushed_exit.png");

  asw::sound::play(music, 255, 128, 1);
}

void Menu::update(StateEngine* engine) {
  // Drop title
  title_y = title_y < 20 ? title_y + (20 - title_y) / 80 : 100;

  // Move city
  auto citySize = asw::util::getTextureSize(city);
  city_x = city_x < -citySize.x ? city_x + citySize.x : city_x - 2;

  // Buttons
  if (start.Clicked())
    setNextState(engine, StateEngine::STATE_MAP);

  if (story.Clicked())
    setNextState(engine, StateEngine::STATE_STORY);

  if (exit.Clicked())
    setNextState(engine, StateEngine::STATE_EXIT);

  // Motherfing goats!
  if (random(0, 80) == 0 || options.Clicked()) {
    goats.push_back(Goat(asw::display::getSize().x,
                         random(0, asw::display::getSize().y),
                         float(random(5, 60)) / 100.0f));
    std::sort(goats.begin(), goats.end());

    if (options.Clicked()) {
      // stop_sample(NOTALLOWED); TODO
      asw::sound::play(NOTALLOWED, 255, 125, 0);
    }
  }

  // Update goats
  for (auto g = goats.begin(); g < goats.end();) {
    g->update();
    g->fall(switchFlipped * 5);
    g->offScreen() ? g = goats.erase(g) : ++g;
  }

  // Flip switch
  if (asw::input::mouse.down[1]) {
    if ((!switchFlipped &&
         collision(595, 607, asw::input::mouse.x, asw::input::mouse.x, 236, 248,
                   asw::input::mouse.y, asw::input::mouse.y)) ||
        (switchFlipped &&
         collision(579, 591, asw::input::mouse.x, asw::input::mouse.x, 235, 247,
                   asw::input::mouse.y, asw::input::mouse.y))) {
      switchFlipped = !switchFlipped;
    }
  }
}

void Menu::draw() {
  // Draw background to screen
  asw::draw::clearColor(asw::util::makeColor(255, 255, 255));

  // Sky
  asw::draw::stretchSprite(sky, 0, 0, asw::display::getSize().x,
                           asw::display::getSize().y);

  // City scroll
  auto citySize = asw::util::getTextureSize(city);
  asw::draw::sprite(city, city_x, asw::display::getSize().y - citySize.y);
  asw::draw::sprite(city, city_x + citySize.x,
                    asw::display::getSize().y - citySize.y);

  // Draw goats
  for (auto g = goats.begin(); g < goats.end(); ++g) {
    g->draw();
  }

  // Stairs
  asw::draw::sprite(background[switchFlipped], 0, 0);

  // Title
  asw::draw::sprite(title, 20, title_y);

  // Buttons
  start.Draw();
  story.Draw();
  options.Draw();
  exit.Draw();

  // Joystick helpers TODO
  // if (num_joysticks > 0) {
  //   masked_blit(little_xbox_buttons, buffer, 60, 0,
  //               start.GetX() + 21 - 4 * start.Hover(),
  //               start.GetY() + 114 - start.Hover(), 20, 20);
  //   masked_blit(little_xbox_buttons, buffer, 40, 0,
  //               story.GetX() + 25 - 4 * story.Hover(),
  //               story.GetY() + 114 - story.Hover(), 20, 20);
  //   masked_blit(little_xbox_buttons, buffer, 0, 0,
  //               options.GetX() + 25 - 4 * options.Hover(),
  //               options.GetY() + 114 - options.Hover(), 20, 20);
  //   masked_blit(little_xbox_buttons, buffer, 20, 0,
  //               exit.GetX() + 25 - 4 * exit.Hover(),
  //               exit.GetY() + 114 - exit.Hover(), 20, 20);
  // }

  // Cursor
  if (start.Hover() || story.Hover() || options.Hover() || exit.Hover()) {
    asw::draw::sprite(cursor2, asw::input::mouse.x, asw::input::mouse.y);
  } else {
    asw::draw::sprite(cursor, asw::input::mouse.x, asw::input::mouse.y);
  }
}
