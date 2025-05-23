#ifndef PLAYER_H
#define PLAYER_H

#include <asw/asw.h>

class Player {
 public:
  Player() = default;

  Player(float x, float y);

  void draw();
  void update(int frame);

 private:
  // Frame
  int frame{0};

  // Variables
  float x, y;

  // Images
  asw::Texture images[8];
};

#endif  // PLAYER_H
