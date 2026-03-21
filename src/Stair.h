#ifndef STAIR_H
#define STAIR_H

#include <asw/asw.h>
#include <array>
#include <vector>

constexpr int IMG_STAIRS = 0;
constexpr int IMG_TOP_RED = 1;
constexpr int IMG_TOP_GREEN = 2;
constexpr int IMG_BRICK = 3;

class Stair {
 public:
  Stair(float x, const std::string& folder);

  // FUNctions
  void update(float distanceRemaining, float speed);
  void draw() const;

  static bool last_stair_placed;

 private:
  float location_y(float last_x);

  float x;
  float y;
  int type;

  std::array<asw::Texture, 4> images;
};

#endif  // STAIR_H
