#include "Player.h"

#include <string>

Player::Player(float x, float y) : x(x), y(y) {
  for (int i = 0; i < 8; i++) {
    images[i] = asw::assets::load_texture("assets/images/player/player_" +
                                          std::to_string(i + 1) + ".png");
  }
}

void Player::draw() {
  asw::draw::sprite(images[frame], asw::Vec2f(x, y));
}

void Player::update(int frame) {
  this->frame = frame;
}
