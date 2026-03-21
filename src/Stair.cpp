#include "Stair.h"

#include "LevelData.h"

bool Stair::last_stair_placed = false;

// Constructor
Stair::Stair(float x, const std::string& folder)
    : x(x), y(location_y(x)), type(0) {
  images[IMG_STAIRS] = asw::assets::load_texture(
      "assets/images/levels/" + folder + "/stairs.png", folder + ":stairs");
  images[IMG_TOP_RED] = asw::assets::load_texture(
      "assets/images/levels/" + folder + "/stage_end_red.png",
      folder + ":stage_end_red");
  images[IMG_TOP_GREEN] = asw::assets::load_texture(
      "assets/images/levels/" + folder + "/stage_end_green.png",
      folder + ":stage_end_green");
  images[IMG_BRICK] = asw::assets::load_texture(
      "assets/images/levels/" + folder + "/brick.png", folder + ":brick");
}

// Update those stairs
void Stair::update(float distanceRemaining, float speed) {
  // Get stair size
  auto stair_size = asw::util::get_texture_size(images[IMG_STAIRS]);
  const auto logical_size = asw::display::get_logical_size();

  // Move
  x -= speed;

  // Go back to start
  if (y > logical_size.y && !last_stair_placed) {
    if (distanceRemaining < logical_size.x - 100) {
      type = 1;
      last_stair_placed = true;
    }

    x += stair_size.x * int(logical_size.x / stair_size.x);
  }

  // Turn green
  if (distanceRemaining == 0 && type == 1) {
    type = 2;
  }

  // Top of map
  y = type == 0 ? location_y(x - 30) : location_y(x);
}

// Line y position
float Stair::location_y(float last_x) {
  const auto logical_size = asw::display::get_logical_size();

  return logical_size.y - ((last_x - logical_size.x / 4) / 30) * 37;
}

// Draw those stairs
// YES WE CAN
void Stair::draw() const {
  // Draw stair and rectangle beside for effect
  const auto stair_size = asw::util::get_texture_size(images[IMG_STAIRS]);
  const auto brick_size = asw::util::get_texture_size(images[IMG_BRICK]);

  for (int i = x + stair_size.x - 30; i < asw::display::get_logical_size().x;
       i += brick_size.x) {
    asw::draw::sprite(images[IMG_BRICK], asw::Vec2f(i, y + stair_size.y));
  }

  asw::draw::sprite(images[type], asw::Vec2f(x, y));
}
