#include "goat.h"

BITMAP *goat::goat_image;

goat::goat(float newX, float newY, float newScale, float newSpeed)
{
  // Setup
  x = newX;
  y = newY;
  scale = newScale;
  speed = newSpeed;
}

goat::~goat() {}

// Draw
void goat::draw( BITMAP* tempImage){
  stretch_sprite( tempImage, goat_image, x, y, goat_image -> w * scale, goat_image -> h * scale);
}

// Update
void goat::update(){
  x -= speed;
}
