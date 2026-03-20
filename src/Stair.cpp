#include "Stair.h"

#include "LevelData.h"
#include "globals.h"

asw::Texture Stair::images[4] = {nullptr};
bool Stair::last_stair_placed = false;

// Constructor
Stair::Stair(float x) {
  this->x = x;

  y = location_y(x);
  type = 0;

  if (images[IMG_STAIRS].get() == nullptr ||
      images[IMG_TOP_RED].get() == nullptr ||
      images[IMG_TOP_GREEN].get() == nullptr ||
      images[IMG_BRICK].get() == nullptr) {
    std::string folder = LevelData::GetLevelData()->GetLevel(levelOn)->folder;

    images[IMG_STAIRS] = asw::assets::load_texture("assets/images/levels/" +
                                                   folder + "/stairs.png");
    images[IMG_TOP_RED] = asw::assets::load_texture(
        "assets/images/levels/" + folder + "/stage_end_red.png");
    images[IMG_TOP_GREEN] = asw::assets::load_texture(
        "assets/images/levels/" + folder + "/stage_end_green.png");
    images[IMG_BRICK] = asw::assets::load_texture("assets/images/levels/" +
                                                  folder + "/brick.png");
  }
}

// Update those stairs
void Stair::update(float distanceRemaining, float speed) {
  // Get stair size
  auto stairSize = asw::util::get_texture_size(images[IMG_STAIRS]);
  const auto logicalSize = asw::display::get_logical_size();

  // Move
  x -= speed;

  // Go back to start
  if (y > logicalSize.y && !last_stair_placed) {
    if (distanceRemaining < logicalSize.x - 100) {
      type = 1;
      last_stair_placed = true;
    }

    x += stairSize.x * int(logicalSize.x / stairSize.x);
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
  const auto logicalSize = asw::display::get_logical_size();

  return logicalSize.y - ((last_x - logicalSize.x / 4) / 30) * 37;
}

// Draw those stairs
// YES WE CAN
void Stair::draw() {
  // Draw stair and rectangle beside for effect
  auto stairSize = asw::util::get_texture_size(images[IMG_STAIRS]);
  auto brickSize = asw::util::get_texture_size(images[IMG_BRICK]);

  for (int i = x + stairSize.x - 30; i < asw::display::get_logical_size().x;
       i += brickSize.x) {
    asw::draw::sprite(images[IMG_BRICK], asw::Vec2f(i, y + stairSize.y));
  }

  asw::draw::sprite(images[type], asw::Vec2f(x, y));
}
