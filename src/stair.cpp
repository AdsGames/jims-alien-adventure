#include "stair.h"

int stair::numberStairs;
const int stair::maxScrollSpeed = 6;
float stair::scrollSpeed;
BITMAP* stair::image;
BITMAP* stair::image_brick;

stair::stair(float newX, float newY){
  x = newX;
  y = newY;

  stairID = numberStairs;
  numberStairs++;
}

stair::~stair(){
  //dtor
}

// Update those stairs
void stair::update( vector<stair>* allStairsCopy){
  // reset stairs
  if( y > SCREEN_H + image -> h){
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
void stair::draw( BITMAP *tempImage){
  // Draw stair and rectangle beside for effect
  for( int i = x + image -> w - 30; i < SCREEN_W; i+= image_brick -> w)
    draw_sprite( tempImage, image_brick, i, y + image -> h);
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
