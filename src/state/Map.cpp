#include "./Map.h"

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
  const auto screen_size = asw::display::get_logical_size();
  ui = std::make_unique<asw::ui::Root>();
  ui->set_size(screen_size.x, screen_size.y);
  ui->root.bg = asw::Color(0, 0, 0, 0);
  ui->ctx.theme.btn_focus_ring = asw::Color(0, 0, 0, 0);

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
  }

  // Start music
  asw::sound::play_music(music);
}

void Map::update(float dt) {
  Scene::update(dt);

  // Controllers step through pins in level order
  controls::update_ui(*ui, controls::Navigation::Cycle);

  // Set cursor
  const auto* hover = ui->ctx.hover;
  if (hover == nullptr || hover == &ui->root) {
    asw::input::set_cursor(asw::input::CursorId::Crosshair);
  } else {
    asw::input::set_cursor(asw::input::CursorId::Pointer);
  }

  // Back to menu
  if (asw::input::get_action_down(controls::UI_BACK)) {
    manager.set_next_scene(States::Menu);
  }
}

void Map::draw() {
  // Draw background to screen
  asw::draw::clear_color(asw::Color(255, 255, 255));

  // Map image
  asw::draw::sprite(map_image, asw::Vec2f(0, 0));

  // Locations
  ui->draw();
}
