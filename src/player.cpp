#include "player.h"

BITMAP* player::image[3];
int player::animation_frame;

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
  draw_sprite( tempImage, image[animation_frame], x, y);
}

void player::update(){
  // Move
  if(key[KEY_SPACE]){
    if( stair::scrollSpeed < 2.8)
      stair::scrollSpeed += 0.2;
  }
  else{
    if( stair::scrollSpeed > 0.1)
      stair::scrollSpeed -= 0.1;
    else{
      stair::scrollSpeed = 0;
    }
  }
}
