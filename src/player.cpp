#include "player.h"

#include <string>

#include "tools.h"

player::player (float x, float y) {
  this -> x = x;
  this -> y = y;
  this -> frame = 0;

  for (int i = 0; i < 8; i++) {
    images[i] = load_png_ex (("images/player/player_" + std::to_string(i + 1) + ".png").c_str());
  }
}

player::~player() {
  for (int i = 0; i < 8; i++) {
    destroy_bitmap(images[i]);
  }
}

int player::getX() {
  return x;
}

int player::getY() {
  return y;
}

int player::getHeight() {
  return images[0] -> h;
}

void player::draw (BITMAP *buffer) {
  draw_sprite (buffer, images[frame], x, y);
}

void player::update(int frame) {
  this -> frame = frame;
}
