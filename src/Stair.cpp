#include "Stair.h"

#include "LevelData.h"
#include "globals.h"
#include "tools.h"

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

    images[IMG_STAIRS] = asw::assets::loadTexture("assets/images/levels/" +
                                                  folder + "/stairs.png");
    images[IMG_TOP_RED] = asw::assets::loadTexture(
        "assets/images/levels/" + folder + "/stage_end_red.png");
    images[IMG_TOP_GREEN] = asw::assets::loadTexture(
        "assets/images/levels/" + folder + "/stage_end_green.png");
    images[IMG_BRICK] = asw::assets::loadTexture("assets/images/levels/" +
                                                 folder + "/brick.png");
  }
}

// Update those stairs
void Stair::update(float distanceRemaining, float speed) {
  // Get stair size
  auto stairSize = asw::util::getTextureSize(images[IMG_STAIRS]);

  // Move
  x -= speed;

  // Go back to start
  if (y > asw::display::getSize().y && !last_stair_placed) {
    if (distanceRemaining < asw::display::getSize().x - 100) {
      type = 1;
      last_stair_placed = true;
    }

    x += stairSize.x * int(asw::display::getSize().x / stairSize.x);
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
  return asw::display::getSize().y -
         ((last_x - asw::display::getSize().x / 4) / 30) * 37;
}

// Draw those stairs
// YES WE CAN
void Stair::draw() {
  // Draw stair and rectangle beside for effect
  auto stairSize = asw::util::getTextureSize(images[IMG_STAIRS]);
  auto brickSize = asw::util::getTextureSize(images[IMG_BRICK]);

  for (int i = x + stairSize.x - 30; i < asw::display::getSize().x;
       i += brickSize.x) {
    asw::draw::sprite(images[IMG_BRICK], i, y + stairSize.y);
  }

  asw::draw::sprite(images[type], x, y);
}
