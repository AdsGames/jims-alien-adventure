#include "player.h"

BITMAP* player::image[8];
int player::animation_frame;

player::player(float newX, float newY)
{
  // Assign variables
  x = newX;
  y = newY;
}

int player::getX(){
  return x;
}

int player::getY(){
  return y;
}

player::~player()
{
}

void player::draw( BITMAP *tempImage){
  // Draw
  draw_sprite( tempImage, image[animation_frame], x, y);
}

void player::update(){
  // Move
  if( y <= (stair::locationOfFinal - (image[0] -> h - 60))){
    stair::scrollSpeed = 0;
  }
}
