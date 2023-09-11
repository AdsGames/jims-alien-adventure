#include "Button.h"

#include "tools.h"

Button::Button() {
  images[0] = nullptr;
  images[1] = nullptr;

  height = 10;
  width = 10;

  this->x = 0;
  this->y = 0;
}

Button::Button(int x, int y) : Button() {
  this->x = x;
  this->y = y;
}

// Load images from file
void Button::SetImages(const std::string image1, const std::string image2) {
  images[0] = asw::assets::loadTexture(image1);
  images[1] = asw::assets::loadTexture(image2);

  // Size
  auto size = asw::util::getTextureSize(images[0]);

  height = size.y;
  width = size.x;
}

bool Button::Hover() {
  return collision(asw::input::mouse.x, asw::input::mouse.x, x, x + width,
                   asw::input::mouse.y, asw::input::mouse.y, y, y + height);
}

bool Button::Clicked() {
  return Hover() && (asw::input::mouse.pressed[1]);
}

int Button::GetX() {
  return x;
}

int Button::GetY() {
  return y;
}

void Button::Draw() {
  if (images[Hover()]) {
    asw::draw::sprite(images[Hover()], x, y);
  }
}
