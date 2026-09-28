#include "MapPin.h"

std::array<asw::Texture, 2> MapPin::pin_images = {nullptr};
int MapPin::pin_count = 0;

// Construct
MapPin::MapPin(int x, int y, std::string& folder, bool completed, int id)
    : transform(asw::Vec2f(x, y), asw::Vec2f(0, 0)),
      id(id),
      completed(completed) {
  if (pin_images[0].get() == nullptr) {
    pin_images[0] =
        asw::assets::load_texture("assets/images/map/pin.png", "pin");
    pin_images[1] =
        asw::assets::load_texture("assets/images/map/pin_grey.png", "pin_grey");
  }

  transform.size = asw::util::get_texture_size(pin_images[0]);
  transform.position.y -= transform.size.y / 2;

  image =
      asw::assets::load_texture("assets/images/levels/" + folder + "/icon.png");
}

// Mouse is hovering
bool MapPin::hover() const {
  const auto& mouse = asw::input::get_mouse();
  return transform.contains(mouse.position);
}

void MapPin::setFocus(bool focus_mode, bool focused) {
  this->focus_mode = focus_mode;
  this->focused = focused;
}

bool MapPin::highlighted() const {
  return focus_mode ? focused : hover();
}

// Get id
int MapPin::getId() const {
  return id;
}

// Draw image
void MapPin::draw() const {
  // Pin
  asw::draw::sprite(pin_images[completed], transform.position);

  // Image, beside the cursor or the focused pin
  if (highlighted()) {
    const auto position =
        focus_mode ? transform.get_center() : asw::input::get_mouse().position;
    asw::draw::sprite(image, position);
  }
}
