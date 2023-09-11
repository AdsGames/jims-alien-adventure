#ifndef GOAT_H
#define GOAT_H

#include <asw/asw.h>

class Goat {
 public:
  Goat(float x, float y, float scale);

  // Functions
  void update();
  void fall(float speed);
  bool offScreen();
  void draw();

  // Sorting operator
  bool operator<(const Goat& g) const {
    return (scale == g.scale) ? y < g.y : scale < g.scale;
  }

 private:
  // Variables
  float x, y;
  float speed;
  float scale;

  // Images
  static asw::Texture goat_image[2];
};

#endif  // GOAT_H
