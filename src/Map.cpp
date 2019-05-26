#include "Map.h"

#include "globals.h"
#include "tools.h"

Map::Map() {
  // Create buffer image
  buffer = create_bitmap (SCREEN_W, SCREEN_H);

  // Load music
  music = load_ogg_ex("music/the-experiment.ogg");

  // Load images
  map_image = load_png_ex("images/map/map.png");
  cursor = load_png_ex("images/map/cursor.png");

  // Allow transparency
  set_alpha_blender();

  // Add locations
  locations.push_back (location(224, 210, 0));
  locations.push_back (location(418, 243, 1));
  locations.push_back (location(236, 216, 2));
  locations.push_back (location(356, 193, 3));
  locations.push_back (location(503, 250, 4));
  locations.push_back (location(570, 217, 5));

  // Cursor position
  position_mouse (SCREEN_W / 2, SCREEN_H / 2);

  // Start music
  play_sample (music, 255, 128, 1000, 1);
}

void Map::update(StateEngine *engine) {
  // Update joystick
  poll_joystick();

  // Change level
  if (mouse_b & 1 || (joystick_enabled && joy[0].button[0].b)) {
    for (unsigned int i = 0; i < locations.size(); i++) {
      if (locations.at (i).Hover()) {
        levelOn = locations.at (i).GetName();
        setNextState (engine, StateEngine::STATE_GAME);
      }
    }
  }

  // Move cursor
  if (joystick_enabled) {
    position_mouse (mouse_x + (joy[0].stick[0].axis[0].pos / 30), mouse_y + (joy[0].stick[0].axis[1].pos / 20));
  }

  // Back to menu
  if (key[KEY_M]) {
    setNextState (engine, StateEngine::STATE_MENU);
  }
}

void Map::draw() {
  // Draw background to screen
  rectfill (buffer, 0, 0, SCREEN_W, SCREEN_H, makecol (255, 255, 255));

  // Map image
  draw_sprite (buffer, map_image, 0, 0);

  // Locations
  for (unsigned int i = 0; i < locations.size(); i++) {
    locations.at (i).Draw (buffer);
  }

  // Cursor
  draw_sprite (buffer, cursor, mouse_x - cursor -> w / 2, mouse_y - cursor -> h / 2);

  // Draw Buffer
  draw_sprite (screen, buffer, 0, 0);
}

Map::~Map() {
  // Destory Bitmaps
  destroy_bitmap (buffer);
  destroy_bitmap (map_image);
  destroy_bitmap (cursor);

  locations.clear();

  // Stop music
  stop_sample (music);
  destroy_sample (music);

  // Fade out
  highcolor_fade_out (16);
}
