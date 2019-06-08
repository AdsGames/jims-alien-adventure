#include "MapPin.h"

#include "tools.h"

BITMAP *MapPin::pin_images[2] = { nullptr };
int MapPin::pin_count = 0;

// Construct
MapPin::MapPin (int x, int y, std::string folder, bool completed, int id) {
  this -> x = x;
  this -> y = y;
  this -> id = id;
  this -> completed = completed;

  if (pin_count == 0)
    load_sprites();

  pin_count++;

  this -> y -= pin_images[0] -> h / 2;
  this -> image = load_png_ex(("images/levels/" + folder + "/icon.png").c_str());
}

// De-construct
MapPin::~MapPin() {
  pin_count--;

  if (pin_count == 0)
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
  draw_trans_sprite (buffer, pin_images[completed], x, y);

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
