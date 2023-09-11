#ifndef BUTTON_H
#define BUTTON_H

#include <asw/asw.h>

class Button {
 public:
  Button();
  Button(int x, int y);

  bool Hover();
  bool Clicked();
  void SetImages(const std::string image1, const std::string image2);

  int GetX();
  int GetY();

  void Draw();

 private:
  int height;
  int width;

  int x;
  int y;

  asw::Texture images[2];
};

#endif
