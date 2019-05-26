#include "location.h"

#include "tools.h"
#include "globals.h"

BITMAP *location::pin_images[2] = { nullptr };
BITMAP *location::images[6] = { nullptr };
int location::location_count = 0;
const int location::num_locations = 6;

// Construct
location::location (int x, int y, int id) {
  this -> x = x;
  this -> y = y;
  this -> id = id;

  if (location_count == 0)
    load_sprites();
  location_count++;

  this -> y -= pin_images[0] -> h / 2;
}

// Copy constructor
location::location (const location &l) {
  x = l.x;
  y = l.y;
  id = l.id;

  if (location_count == 0)
    load_sprites();
  location_count++;
}

// De-construct
location::~location() {
  location_count--;
  if (location_count == 0)
    unload_sprites();
}

// Load images
void location::load_sprites() {
  images[0] = load_png_ex("images/map/icon_cntower.png");
  images[1] = load_png_ex("images/map/icon_pyramids.png");
  images[2] = load_png_ex("images/map/icon_statueofliberty.png");
  images[3] = load_png_ex("images/map/icon_stonehenge.png");
  images[4] = load_png_ex("images/map/icon_tajmahal.png");
  images[5] = load_png_ex("images/map/icon_wallofchina.png");

  pin_images[0] = load_png_ex("images/map/pin.png");
  pin_images[1] = load_png_ex("images/map/pin_grey.png");
}

// Unload images
void location::unload_sprites() {
  for (int i = 0; i < num_locations; i++) {
    destroy_bitmap(images[i]);
  }

  destroy_bitmap(pin_images[0]);
  destroy_bitmap(pin_images[1]);
}

// Draw image
void location::Draw (BITMAP *buffer) {
  // Pin
  if (beaten_levels[id]) {
    draw_trans_sprite (buffer, pin_images[1], x, y);
  }
  else {
    draw_trans_sprite (buffer, pin_images[0], x, y);
  }

  // Image
  if (Hover()) {
    draw_sprite (buffer, images[id], mouse_x, mouse_y);
  }
}

// Mouse is hovering
bool location::Hover() {
  return collision (x - 5, x + pin_images[0] -> w + 5, mouse_x, mouse_x, y, y + pin_images[0] -> h, mouse_y, mouse_y);
}

// Mouse is hovering
std::string location::GetName() {
  switch (id) {
    case 0:
      return "cn_tower";
    case 1:
      return "pyramids";
    case 2:
      return "statue_of_liberty";
    case 3:
      return "stone_henge";
    case 4:
      return "taj_mahal";
    case 5:
      return "wall_of_china";
    default:
      return "unknown_location";
  }
}
