#include "goat.h"


BITMAP *goat::goat_image[2];

goat::goat(float newX, float newY, float newScale, float newSpeed){
  // Setup
  x = newX;
  y = newY;
  scale = newScale;
  speed = newSpeed;
}

goat::~goat() {}

// Draw
void goat::draw( BITMAP* tempImage){
  stretch_sprite( tempImage, goat_image[random( 0, 1)], x, y, goat_image[0] -> w * scale, goat_image[1] -> h * scale);
}

// Update
void goat::update(){
  x -= speed;
}

void goat::fall(float newSpeed){
  y+=newSpeed;
}
