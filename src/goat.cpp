#include "goat.h"


BITMAP *goat::goat_image[2];

goat::goat(float newX, float newY, float newScale, float newSpeed){
  // Setup
  x = newX;
  y = newY;
  scale = newScale;
  speed = newSpeed;
  offScreen = false;
}

goat::~goat() {

}

// Draw
void goat::draw( BITMAP* tempImage){
  stretch_sprite( tempImage, goat_image[random( 0, 1)], x, y, goat_image[0] -> w * scale, goat_image[1] -> h * scale);
}

// Update
void goat::update(){
  x -= speed;

  if( x + goat_image[0] -> w - speed < 0 || x - speed > SCREEN_W || y > SCREEN_H || y + goat_image[0] -> h < 0)
    offScreen = true;
}

// Kill
bool goat::kill(){
  return offScreen;
}

// Fall!
void goat::fall(float newSpeed){
  y+=newSpeed;
}
