#include "Button.h"

#include "tools.h"

Button::Button(float x, float y) : Button() {
  transform.position.x = x;
  transform.position.y = y;
}

// Load images from file
void Button::setImages(const std::string& image1, const std::string& image2) {
  images[0] = asw::assets::loadTexture(image1);
  images[1] = asw::assets::loadTexture(image2);
  transform.size = asw::util::getTextureSize(images[0]);
}

bool Button::hover() {
  return transform.contains(asw::input::mouse.x, asw::input::mouse.y);
}

bool Button::clicked() {
  return hover() && asw::input::wasButtonPressed(asw::input::MouseButton::LEFT);
}

void Button::draw() {
  if (images[hover()]) {
    asw::draw::sprite(images[hover()], transform.position);
  }
}
