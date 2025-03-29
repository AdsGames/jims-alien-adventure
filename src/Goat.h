#pragma once

#include <asw/asw.h>
#include <array>

class Goat {
 public:
  Goat(float x, float y, float scale);

  // Functions
  void update(float deltaTime);

  void setFalling(bool falling);

  bool offScreen();

  void draw();

  // Sorting operator
  bool operator<(const Goat& g) const {
    if (transform.size.x == g.transform.size.x) {
      return transform.position.y < g.transform.position.y;
    }
    return transform.size.x < g.transform.size.x;
  }

 private:
  // Variables
  asw::Quad<float> transform;
  float speed;
  bool falling{false};

  // Images
  static std::array<asw::Texture, 2> goat_image;

  // Goat speed multiplier
  static constexpr float goat_speed_multiplier = 0.1875F;
  static constexpr float goat_fall_speed_multiplier = 16.0F;
};
