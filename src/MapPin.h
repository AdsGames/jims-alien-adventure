#ifndef MAP_PIN_H
#define MAP_PIN_H

#include <asw/asw.h>
#include <array>
#include <string>

// Location for map
class MapPin {
 public:
  MapPin(int x, int y, std::string& folder, bool completed, int id);

  void draw();

  bool hover() const;

  int getId() const;

 private:
  asw::Texture image;
  static std::array<asw::Texture, 2> pin_images;
  static int pin_count;

  asw::Quad<float> transform;

  int id;
  bool completed;
};

#endif  // MAP_PIN_H
