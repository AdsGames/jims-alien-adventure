#ifndef GOAT_H
#define GOAT_H

#include <allegro.h>

class Goat {
 public:
  Goat(float x, float y, float scale);
  Goat(const Goat& g);
  virtual ~Goat();

  // Functions
  void update();
  void fall(float speed);
  bool offScreen();
  void draw(BITMAP* buffer);

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
  static BITMAP* goat_image[2];
  static int goat_count;

  void load_sprites();
  void unload_sprites();
};

#endif  // GOAT_H
