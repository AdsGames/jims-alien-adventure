#include "./Menu.h"

#include <algorithm>

#include "../tools.h"

void Menu::init() {
  // Load music
  music = asw::assets::load_music("assets/music/JAA-Theme.ogg");

  // Load sound
  NOTALLOWED = asw::assets::load_sample("assets/sounds/goat.wav");

  // Load images
  background[0] = asw::assets::load_texture("assets/images/menu/menu.png");
  background[1] = asw::assets::load_texture("assets/images/menu/menu_2.png");

  title = asw::assets::load_texture("assets/images/menu/title.png");
  sky = asw::assets::load_texture(
      "assets/images/levels/statue_of_liberty/sky.png");
  city = asw::assets::load_texture(
      "assets/images/levels/statue_of_liberty/parallax.png");
  cursor = asw::assets::load_texture("assets/images/menu/cursor1.png");
  cursor2 = asw::assets::load_texture("assets/images/menu/cursor2.png");

  little_xbox_buttons =
      asw::assets::load_texture("assets/images/menu/angle_buttons.png");

  // Sets Font
  font = asw::assets::load_font("assets/fonts/dosis.ttf", 12);

  // Variable set
  title_y = -(asw::util::get_texture_size(title).y + 20);
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

  asw::sound::play_music(music, 255);
}

void Menu::update(float dt) {
  Scene::update(dt);
  const auto& mouse = asw::input::get_mouse();

  // Drop title
  if (title_y <= 20.0F) {
    title_y += ((20.0F - title_y) / 80.0F) * title_speed_multiplier * dt;
  } else {
    title_y = 20.0F;
  }

  // Move city
  auto citySize = asw::util::get_texture_size(city);
  if (city_x < -citySize.x) {
    city_x = city_x + citySize.x;
  } else {
    city_x -= city_speed_multiplier * dt;
  }

  // Buttons
  if (start.clicked()) {
    manager.set_next_scene(States::Map);
  }

  if (story.clicked()) {
    manager.set_next_scene(States::Story);
  }

  if (exit.clicked()) {
    asw::core::exit();
  }

  if (options.clicked()) {
    asw::sound::play(NOTALLOWED);
  }

  // Motherfing goats!
  if (asw::random::between(0, 80) == 0 || options.clicked()) {
    goats.emplace_back(
        asw::display::get_logical_size().x,
        asw::random::between(0, asw::display::get_logical_size().y),
        asw::random::between(5.0F, 60.0F) / 100.0F);
    std::sort(goats.begin(), goats.end());
  }

  // Update goats
  for (auto g = goats.begin(); g < goats.end();) {
    g->update(dt);
    g->setFalling(switchFlipped);
    g->offScreen() ? g = goats.erase(g) : ++g;
  }

  // Flip switch
  if (asw::input::get_mouse_button_down(asw::input::MouseButton::Left)) {
    const asw::Quadf switchArea = switchFlipped ? asw::Quadf(579, 235, 12, 12)
                                                : asw::Quadf(595, 236, 12, 12);

    if (switchArea.contains(mouse.position)) {
      switchFlipped = !switchFlipped;
    }
  }

  // Cursor
  if (start.hover() || story.hover() || options.hover() || exit.hover()) {
    asw::input::set_cursor(asw::input::CursorId::Pointer);
  } else {
    asw::input::set_cursor(asw::input::CursorId::Default);
  }
}

void Menu::draw() {
  const auto logicalSize = asw::display::get_logical_size();

  // Sky
  asw::draw::stretch_sprite(sky,
                            asw::Quadf(0, 0, logicalSize.x, logicalSize.y));

  // City scroll
  auto citySize = asw::util::get_texture_size(city);
  asw::draw::sprite(city, asw::Vec2f(city_x, logicalSize.y - citySize.y));
  asw::draw::sprite(
      city, asw::Vec2f(city_x + citySize.x, logicalSize.y - citySize.y));

  // Draw goats
  for (auto g = goats.begin(); g < goats.end(); ++g) {
    g->draw();
  }

  // Stairs
  asw::draw::sprite(background[switchFlipped], asw::Vec2f(0, 0));

  // Title
  asw::draw::sprite(title, asw::Vec2f(20, title_y));

  // Buttons
  start.draw();
  story.draw();
  options.draw();
  exit.draw();
}
