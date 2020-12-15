#ifndef PLAYER_H
#define PLAYER_H

#include <allegro.h>

class Player {
 public:
  Player(float x, float y);
  Player(const Player& p);
  virtual ~Player();

  void draw(BITMAP* buffer);
  void update(int frame);

 private:
  // Frame
  int frame;

  // Variables
  float x, y;

  // Images
  BITMAP* images[8];
};

#endif  // PLAYER_H
