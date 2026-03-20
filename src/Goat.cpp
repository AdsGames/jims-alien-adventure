#include "Goat.h"

std::array<asw::Texture, 2> Goat::goat_image = {nullptr};

Goat::Goat(float x, float y, float scale)
    : transform(x, y, 0, 0), speed(scale * goat_speed_multiplier) {
  if (goat_image[0].get() == nullptr || goat_image[1].get() == nullptr) {
    goat_image[0] = asw::assets::load_texture("assets/images/goat_alien.png");
    goat_image[1] = asw::assets::load_texture("assets/images/goat_alien_2.png");
  }

  transform.size = asw::util::get_texture_size(goat_image[0]) * scale;
}

// Update
void Goat::update(float dt) {
  transform.position.x -= speed * dt;

  if (falling) {
    transform.position.y += speed * goat_fall_speed_multiplier * dt;
  }
}

// Kill
bool Goat::offScreen() const {
  return !transform.collides(asw::Quadf(0.0F, 0.0F,
                                        asw::display::get_logical_size().x,
                                        asw::display::get_logical_size().y));
}

// Fall!
void Goat::setFalling(bool falling) {
  this->falling = falling;
}

// Draw
void Goat::draw() const {
  asw::draw::stretch_sprite(goat_image[asw::random::between(0, 1)], transform);
}
