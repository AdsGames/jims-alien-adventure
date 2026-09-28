#include "./Map.h"

#include "../Controls.h"
#include "../globals.h"

void Map::init() {
  // Load music
  music = asw::assets::load_music("assets/music/the-experiment.ogg");

  // Load images
  map_image = asw::assets::load_texture("assets/images/map/map.png");

  auto level_data = LevelData("assets/levels.json");

  // Add pins
  pins.clear();
  focus = 0;
  for (int i = 0; i < level_data.GetNumLevels(); i++) {
    auto l = level_data.GetLevel(i);
    if (!l.has_value()) {
      continue;
    }

    pins.emplace_back(l->pin_x, l->pin_y, l->folder, l->completed, l->id);
  }

  // Start music
  asw::sound::play_music(music);
}

void Map::update(float dt) {
  Scene::update(dt);

  // Controller players step through pins instead of using the mouse
  const bool controller = controls::using_controller();
  asw::input::set_cursor_visible(!controller);

  const int pin_count = static_cast<int>(pins.size());
  if (controller && pin_count > 0) {
    if (asw::input::get_action_down(controls::UI_RIGHT) ||
        asw::input::get_action_down(controls::UI_DOWN)) {
      focus = (focus + 1) % pin_count;
    }

    if (asw::input::get_action_down(controls::UI_LEFT) ||
        asw::input::get_action_down(controls::UI_UP)) {
      focus = (focus + pin_count - 1) % pin_count;
    }
  }

  for (int i = 0; i < pin_count; i++) {
    pins[i].setFocus(controller, i == focus);
  }

  // Pin logic
  auto is_hovering = false;
  for (const auto& p : pins) {
    if (p.highlighted()) {
      is_hovering = true;

      const bool picked =
          controller ? asw::input::get_action_down(controls::UI_CONFIRM)
                     : asw::input::get_mouse_button_down(
                           asw::input::MouseButton::Left);

      if (picked) {
        levelOn = p.getId();
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
  for (const auto& p : pins) {
    p.draw();
  }
}
