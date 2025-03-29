#include "Player.h"

#include <string>

#include "tools.h"

Player::Player(float x, float y) : x(x), y(y) {
  for (int i = 0; i < 8; i++) {
    images[i] = asw::assets::loadTexture("assets/images/player/player_" +
                                         std::to_string(i + 1) + ".png");
  }
}

void Player::draw() {
  asw::draw::sprite(images[frame], asw::Vec2<float>(x, y));
}

void Player::update(int frame) {
  this->frame = frame;
}
