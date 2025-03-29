#ifndef MAP_PIN_H
#define MAP_PIN_H

#include <asw/asw.h>
#include <string>

// Location for map
class MapPin {
 public:
  MapPin(int x, int y, std::string& folder, bool completed, int id);

  void Draw();
  bool hover();
  int GetID();

 private:
  asw::Texture image;
  static asw::Texture pin_images[2];
  static int pin_count;

  int id;
  int x, y;
  bool completed;
};

#endif  // MAP_PIN_H
