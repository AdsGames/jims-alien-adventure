#include "./Menu.h"

#include <algorithm>
#include <utility>

#include "../Controls.h"

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
  const auto screen_size = asw::display::get_logical_size();
  ui = std::make_unique<asw::ui::Root>();
  ui->set_size(screen_size.x, screen_size.y);
  ui->root.bg = asw::Color(0, 0, 0, 0);
  ui->ctx.theme.btn_focus_ring = asw::Color(0, 0, 0, 0);

  addButton("play", asw::Vec2f(30, 190),
            [this]() { manager.set_next_scene(States::Map); });

  addButton("story", asw::Vec2f(195, 190),
            [this]() { manager.set_next_scene(States::Story); });

  addButton("options", asw::Vec2f(30, 300), [this]() {
    asw::sound::play(NOTALLOWED);
    addGoat();
  });

  addButton("exit", asw::Vec2f(195, 300), []() { asw::core::exit(); });

  asw::sound::play_music(music);
}

void Menu::addButton(const std::string& name,
                     const asw::Vec2f& position,
                     std::function<void()> on_click) {
  auto& button = ui->root.add_child<asw::ui::Button>();
  button.draw_background = false;
  button.set_texture(
      asw::assets::load_texture("assets/images/menu/button_" + name + ".png"),
      true);
  button.texture_hover = asw::assets::load_texture(
      "assets/images/menu/button_pushed_" + name + ".png");
  button.transform.position = position;
  button.on_click = std::move(on_click);
}

void Menu::addGoat() {
  goats.emplace_back(
      asw::display::get_logical_size().x,
      asw::random::between(0, asw::display::get_logical_size().y),
      asw::random::between(5.0F, 60.0F) / 100.0F);
  std::sort(goats.begin(), goats.end());
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
  controls::update_ui(*ui);

  // Motherfing goats!
  if (asw::random::between(0, 80) == 0) {
    addGoat();
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
  const auto* hover = ui->ctx.hover;
  if (hover == nullptr || hover == &ui->root) {
    asw::input::set_cursor(asw::input::CursorId::Default);
  } else {
    asw::input::set_cursor(asw::input::CursorId::Pointer);
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
  ui->draw();
}
