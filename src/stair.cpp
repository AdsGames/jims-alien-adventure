#include "stair.h"

int stair::numberStairs;
float stair::scrollSpeed;
BITMAP* stair::image;

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

  // Move
  x -= scrollSpeed;
  y = location_y(x);
}

// Draw those stairs
void stair::draw( BITMAP *tempImage){
  // Draw stair and rectangle beside for effect
  rectfill( tempImage, x + 30, y, SCREEN_W, y + image -> h - 1, makecol( 115, 40, 0));
  draw_sprite( tempImage, image, x, y);
}

// Line y position
float stair::location_y( float oldX){
  return SCREEN_H - (oldX/30) * 37;
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
