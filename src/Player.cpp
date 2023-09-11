#include "Player.h"

#include <string>

#include "tools.h"

Player::Player(float x, float y) {
  this->x = x;
  this->y = y;
  this->frame = 0;

  for (int i = 0; i < 8; i++) {
    images[i] = asw::assets::loadTexture("assets/images/player/player_" +
                                         std::to_string(i + 1) + ".png");
  }
}

void Player::draw() {
  asw::draw::sprite(images[frame], x, y);
}

void Player::update(int frame) {
  this->frame = frame;
}
