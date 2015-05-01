#include "player.h"

player::player(float newX, float newY, BITMAP *newImage)
{
  // Assign variables
  x = newX;
  y = newY;

  image = newImage;
}

player::~player()
{
  //dtor
}

void player::draw( BITMAP *tempImage){
  // Draw
  draw_sprite( tempImage, image, x, y);
}

void player::update(){
  // Move

}
