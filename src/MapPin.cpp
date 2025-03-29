#include "MapPin.h"

#include "tools.h"

asw::Texture MapPin::pin_images[2] = {nullptr};
int MapPin::pin_count = 0;

// Construct
MapPin::MapPin(int x, int y, std::string& folder, bool completed, int id) {
  this->x = x;
  this->y = y;
  this->id = id;
  this->completed = completed;

  if (pin_images[0].get() == nullptr) {
    pin_images[0] = asw::assets::loadTexture("assets/images/map/pin.png");
    pin_images[1] = asw::assets::loadTexture("assets/images/map/pin_grey.png");
  }

  auto size = asw::util::getTextureSize(pin_images[0]);

  this->y -= size.y / 2;
  this->image =
      asw::assets::loadTexture("assets/images/levels/" + folder + "/icon.png");
}

// Draw image
void MapPin::Draw() {
  // Pin
  asw::draw::sprite(pin_images[completed], asw::Vec2<float>(x, y));

  // Image
  if (hover()) {
    asw::draw::sprite(
        image, asw::Vec2<float>(asw::input::mouse.x, asw::input::mouse.y));
  }
}

// Mouse is hovering
bool MapPin::hover() {
  auto size = asw::util::getTextureSize(pin_images[0]);
  return collision(x - 5, x + size.x + 5, asw::input::mouse.x,
                   asw::input::mouse.x, y, y + size.y, asw::input::mouse.y,
                   asw::input::mouse.y);
}

// Get id
int MapPin::GetID() {
  return id;
}
