#include "./Map.h"

#include <cstddef>
#include <vector>

#include "../Controls.h"
#include "../MapPin.h"
#include "../globals.h"

void Map::init() {
  // Load music
  music = asw::assets::load_music("assets/music/the-experiment.ogg");

  // Load images
  map_image = asw::assets::load_texture("assets/images/map/map.png");

  auto level_data = LevelData("assets/levels.json");

  // Add pins
  ui = std::make_unique<asw::ui::Root>();
  ui->ctx.navigation = controls::ui_navigation();
  ui->ctx.theme.focus_ring.width = 0;
  ui->on_back = [this]() { manager.set_next_scene(States::Menu); };

  std::vector<MapPin*> pins;

  for (int i = 0; i < level_data.GetNumLevels(); i++) {
    auto l = level_data.GetLevel(i);
    if (!l.has_value()) {
      continue;
    }

    auto& pin =
        ui->root.add_child<MapPin>(l->pin_x, l->pin_y, l->folder, l->completed);
    pin.on_click = [this, id = l->id]() {
      levelOn = id;
      manager.set_next_scene(States::Game);
    };
    pins.push_back(&pin);
  }

  // Directions step through pins in level order: right and down to the next,
  // left and up to the previous, wrapping
  const auto count = pins.size();
  for (std::size_t i = 0; i < count; i++) {
    auto* next = pins[(i + 1) % count];
    auto* prev = pins[(i + count - 1) % count];
    pins[i]->nav_right = next;
    pins[i]->nav_down = next;
    pins[i]->nav_left = prev;
    pins[i]->nav_up = prev;
  }

  // Start music
  asw::sound::play_music(music);
}

void Map::update(float dt) {
  Scene::update(dt);

  // Pins, back goes to the menu
  ui->update();

  // Set cursor
  controls::update_cursor(*ui, asw::input::CursorId::Crosshair);
}

void Map::draw() {
  // Draw background to screen
  asw::draw::clear_color(asw::Color(255, 255, 255));

  // Map image
  asw::draw::sprite(map_image, asw::Vec2f(0, 0));

  // Locations
  ui->draw();
}
