#pragma once

#include <asw/asw.h>
#include <array>

class Goat {
 public:
  Goat(float x, float y, float scale);

  // Functions
  void update(float deltaTime);

  void setFalling(bool falling);

  bool offScreen() const;

  void draw() const;

  // Sorting operator
  friend bool operator<(const Goat& a, const Goat& b) {
    if (a.transform.size.x == b.transform.size.x) {
      return a.transform.position.y < b.transform.position.y;
    }
    return a.transform.size.x < b.transform.size.x;
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
