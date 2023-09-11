#include "Goat.h"

#include "tools.h"

asw::Texture Goat::goat_image[2] = {nullptr};
int Goat::goat_count = 0;

Goat::Goat(float x, float y, float scale) {
  this->x = x;
  this->y = y;
  this->scale = scale;
  this->speed = scale * 3.0f;

  if (goat_image[0].get() == nullptr || goat_image[1].get() == nullptr) {
    goat_image[0] = asw::assets::loadTexture("assets/images/goat_alien.png");
    goat_image[1] = asw::assets::loadTexture("assets/images/goat_alien_2.png");
  }
}

Goat::Goat(const Goat& g) {
  this->x = g.x;
  this->y = g.y;
  this->scale = g.scale;
  this->speed = g.speed;
}

// Update
void Goat::update() {
  x -= speed;
}

// Kill
bool Goat::offScreen() {
  auto size = asw::util::getTextureSize(goat_image[0]);
  return (x + size.x - speed < 0 || x - speed > asw::display::getSize().x ||
          y > asw::display::getSize().y || y + size.y < 0);
}

// Fall!
void Goat::fall(float speed) {
  y += speed;
}

// Draw
void Goat::draw() {
  auto size = asw::util::getTextureSize(goat_image[0]);
  asw::draw::stretchSprite(goat_image[random(0, 1)], x, y, size.x * scale,
                           size.y * scale);
}
