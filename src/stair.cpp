#include "stair.h"
#include "globals.h"

int stair::numberStairs;
const int stair::maxScrollSpeed = 6;
float stair::scrollSpeed;
BITMAP* stair::image;
BITMAP* stair::image_brick;
BITMAP* stair::stage_end_red;

stair::stair(float newX, float newY, int newType){
  x = newX;
  y = newY;
  type = newType;

  stairID = numberStairs;
  numberStairs++;
}

stair::~stair(){
  //dtor
}

// Update those stairs
void stair::update( vector<stair>* allStairsCopy){
  // reset stairs
  if( y > SCREEN_H + image -> h && !is_game_done){
    x = allStairsCopy -> at(find_bottom_stair(stairID)).x + 30;
    y = location_y(x);
  }
}

void stair::movement(){
  // Move
  x -= scrollSpeed;
  y = location_y(x);
}

// Draw those stairs
// YES WE CAN
void stair::draw( BITMAP *tempImage){
  // Draw stair and rectangle beside for effect
  for( int i = x + image -> w - 30; i < SCREEN_W; i+= image_brick -> w){
    if(type==0)draw_sprite( tempImage, image_brick, i, y + image -> h);
    if(type==1)draw_sprite( tempImage, stage_end_red, i, y + image -> h);
  }
  draw_sprite( tempImage, image, x, y);
}

// Line y position
float stair::location_y( float oldX){
  return (SCREEN_H - ((oldX-SCREEN_W/2)/30) * 37);
}

// Line y position
int stair::find_bottom_stair( int stairIndex){
  // New index
  int bottomIndex = stairIndex - 1;

  // Too High? Wrap around (only happens when number is max)
  if( bottomIndex < 0){
    bottomIndex = numberStairs - 1;
  }

  return bottomIndex;
}
