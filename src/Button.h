#pragma once

#include <asw/asw.h>
#include <array>

class Button {
 public:
  Button() = default;
  Button(float x, float y);

  bool hover() const;
  bool clicked() const;
  void setImages(const std::string& image1, const std::string& image2);

  // In focus mode the button highlights and clicks when focused, not by mouse
  void setFocus(bool focus_mode, bool focused);

  // Hovered by the mouse, or focused in focus mode
  bool highlighted() const;

  void draw();

 private:
  asw::Quadf transform;

  bool focus_mode{false};
  bool focused{false};

  std::array<asw::Texture, 2> images;
};
