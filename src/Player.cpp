#include "Player.h"

#include <string>

#include "tools.h"

Player::Player (float x, float y) {
  this -> x = x;
  this -> y = y;
  this -> frame = 0;

  for (int i = 0; i < 8; i++) {
    images[i] = load_png_ex (("images/player/player_" + std::to_string(i + 1) + ".png").c_str());
  }
}

Player::~Player() {
  for (int i = 0; i < 8; i++) {
    destroy_bitmap(images[i]);
  }
}

void Player::draw (BITMAP *buffer) {
  draw_sprite (buffer, images[frame], x, y);
}

void Player::update(int frame) {
  this -> frame = frame;
}
