#pragma once

#include <asw/asw.h>
#include <array>

class Button {
 public:
  Button() = default;
  Button(float x, float y);

  bool hover();
  bool clicked();
  void setImages(const std::string& image1, const std::string& image2);

  void draw();

 private:
  asw::Quad<float> transform;

  std::array<asw::Texture, 2> images;
};
