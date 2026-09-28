#ifndef MAP_PIN_H
#define MAP_PIN_H

#include <asw/asw.h>
#include <array>
#include <string>

// Location for map, shows the level icon while hovered or focused
class MapPin : public asw::ui::Button {
 public:
  MapPin(int x, int y, const std::string& folder, bool completed);

  void draw(asw::ui::Context& ctx) override;

 private:
  asw::Texture image;
  static std::array<asw::Texture, 2> pin_images;
};

#endif  // MAP_PIN_H
