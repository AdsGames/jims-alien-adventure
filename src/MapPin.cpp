#include "MapPin.h"

#include "tools.h"
#include "globals.h"
#include "LevelData.h"

BITMAP *MapPin::pin_images[2] = { nullptr };
int MapPin::location_count = 0;
const int MapPin::num_locations = 6;

// Construct
MapPin::MapPin (int x, int y, int id) {
  this -> x = x;
  this -> y = y;
  this -> id = id;

  if (location_count == 0)
    load_sprites();
  location_count++;

  this -> y -= pin_images[0] -> h / 2;
  this -> image = load_png_ex(("images/levels/" + LevelData::GetLevelData() -> GetLevel(id) -> folder + "/icon.png").c_str());
}

// De-construct
MapPin::~MapPin() {
  location_count--;
  if (location_count == 0)
    unload_sprites();

  destroy_bitmap(image);
}

// Load images
void MapPin::load_sprites() {
  pin_images[0] = load_png_ex("images/map/pin.png");
  pin_images[1] = load_png_ex("images/map/pin_grey.png");
}

// Unload images
void MapPin::unload_sprites() {
  destroy_bitmap(pin_images[0]);
  destroy_bitmap(pin_images[1]);
}

// Draw image
void MapPin::Draw (BITMAP *buffer) {
  // Pin
  if (LevelData::GetLevelData() -> GetLevel(id) -> completed) {
    draw_trans_sprite (buffer, pin_images[1], x, y);
  }
  else {
    draw_trans_sprite (buffer, pin_images[0], x, y);
  }

  // Image
  if (Hover()) {
    draw_sprite (buffer, image, mouse_x, mouse_y);
  }
}

// Mouse is hovering
bool MapPin::Hover() {
  return collision (x - 5, x + pin_images[0] -> w + 5, mouse_x, mouse_x, y, y + pin_images[0] -> h, mouse_y, mouse_y);
}

// Get id
int MapPin::GetID() {
  return id;
}
