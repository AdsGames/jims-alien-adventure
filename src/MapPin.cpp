#include "MapPin.h"

std::array<asw::Texture, 2> MapPin::pin_images = {nullptr};
int MapPin::pin_count = 0;

// Construct
MapPin::MapPin(int x, int y, std::string& folder, bool completed, int id)
    : transform(asw::Vec2<float>(x, y), asw::Vec2<float>(0, 0)),
      id(id),
      completed(completed) {
  if (pin_images[0].get() == nullptr) {
    pin_images[0] = asw::assets::loadTexture("assets/images/map/pin.png");
    pin_images[1] = asw::assets::loadTexture("assets/images/map/pin_grey.png");
  }

  transform.size = asw::util::getTextureSize(pin_images[0]);
  transform.position.y -= transform.size.y / 2;

  image =
      asw::assets::loadTexture("assets/images/levels/" + folder + "/icon.png");
}

// Mouse is hovering
bool MapPin::hover() const {
  return transform.contains(asw::input::mouse.x, asw::input::mouse.y);
}

// Get id
int MapPin::getId() const {
  return id;
}

// Draw image
void MapPin::draw() {
  // Pin
  asw::draw::sprite(pin_images[completed], transform.position);

  // Image
  if (hover()) {
    asw::draw::sprite(
        image, asw::Vec2<float>(asw::input::mouse.x, asw::input::mouse.y));
  }
}
