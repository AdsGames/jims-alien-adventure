#include "player.h"

BITMAP* player::image;

player::player(float newX, float newY)
{
  // Assign variables
  x = newX;
  y = newY;
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
  if(key[KEY_SPACE]){
    if( stair::scrollSpeed < 3)
      stair::scrollSpeed += 0.2;
  }
  else{
    if( stair::scrollSpeed > 1)
      stair::scrollSpeed -= 0.1;
  }
}
