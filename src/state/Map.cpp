#include "./Map.h"

#include "../globals.h"

void Map::init() {
  // Load music
  music = asw::assets::load_music("assets/music/the-experiment.ogg");

  // Load images
  map_image = asw::assets::load_texture("assets/images/map/map.png");

  // Add pins
  for (int i = 0; i < LevelData::GetLevelData()->GetNumLevels(); i++) {
    Level* l = LevelData::GetLevelData()->GetLevel(i);
    pins.push_back(
        new MapPin(l->pin_x, l->pin_y, l->folder, l->completed, l->id));
  }

  // Start music
  asw::sound::play_music(music, 255);
}

void Map::update(float dt) {
  Scene::update(dt);

  // Pin logic
  auto is_hovering = false;
  for (auto p : pins) {
    if (p->hover()) {
      is_hovering = true;

      if (asw::input::get_mouse_button_down(asw::input::MouseButton::Left)) {
        levelOn = p->getId();
        manager.set_next_scene(States::Game);
      }
    }
  }

  // Set cursor
  if (!is_hovering) {
    asw::input::set_cursor(asw::input::CursorId::Crosshair);
  } else {
    asw::input::set_cursor(asw::input::CursorId::Pointer);
  }

  // Back to menu
  if (asw::input::get_key_down(asw::input::Key::Escape)) {
    manager.set_next_scene(States::Menu);
  }
}

void Map::draw() {
  // Draw background to screen
  asw::draw::clear_color(asw::Color(255, 255, 255));

  // Map image
  asw::draw::sprite(map_image, asw::Vec2f(0, 0));

  // Locations
  for (auto p : pins) {
    p->draw();
  }
}
