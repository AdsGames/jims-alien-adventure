#include "Button.h"

Button::Button(float x, float y) : Button() {
  transform.position.x = x;
  transform.position.y = y;
}

// Load images from file
void Button::setImages(const std::string& image1, const std::string& image2) {
  images[0] = asw::assets::load_texture(image1);
  images[1] = asw::assets::load_texture(image2);
  transform.size = asw::util::get_texture_size(images[0]);
}

bool Button::hover() {
  return transform.contains(asw::input::mouse.position);
}

bool Button::clicked() {
  return hover() &&
         asw::input::get_mouse_button_down(asw::input::MouseButton::Left);
}

void Button::draw() {
  if (images[hover()]) {
    asw::draw::sprite(images[hover()], transform.position);
  }
}
