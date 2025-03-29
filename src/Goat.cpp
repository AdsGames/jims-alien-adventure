#include "Goat.h"

std::array<asw::Texture, 2> Goat::goat_image = {nullptr};

Goat::Goat(float x, float y, float scale)
    : transform(x, y, 0, 0), speed(scale * goat_speed_multiplier) {
  if (goat_image[0].get() == nullptr || goat_image[1].get() == nullptr) {
    goat_image[0] = asw::assets::loadTexture("assets/images/goat_alien.png");
    goat_image[1] = asw::assets::loadTexture("assets/images/goat_alien_2.png");
  }

  transform.size = asw::util::getTextureSize(goat_image[0]) * scale;
}

// Update
void Goat::update(float deltaTime) {
  transform.position.x -= speed * deltaTime;

  if (falling) {
    transform.position.y += speed * goat_fall_speed_multiplier * deltaTime;
  }
}

// Kill
bool Goat::offScreen() {
  return !transform.contains(
      asw::Quad<float>(0.0F, 0.0F, asw::display::getLogicalSize().x,
                       asw::display::getLogicalSize().y));
}

// Fall!
void Goat::setFalling(bool falling) {
  this->falling = falling;
}

// Draw
void Goat::draw() {
  asw::draw::stretchSprite(goat_image[asw::random::between(0, 1)], transform);
}
