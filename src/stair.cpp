#include "stair.h"
#include "globals.h"

int stair::numberStairs;
const int stair::maxScrollSpeed = 6;
float stair::scrollSpeed;
float stair::locationOfFinal = 0;
BITMAP* stair::image;
BITMAP* stair::image_brick;
BITMAP* stair::stage_end_red;
BITMAP* stair::stage_end_green;
bool stair::final_stair_placed;

stair::stair(float newX, float newY, int newType){
  x = newX;
  y = newY;
  type = newType;

  stairID = numberStairs;
  numberStairs++;

  transparency_bitmap = create_bitmap( SCREEN_W, SCREEN_H);
  rectfill( transparency_bitmap, 0, 0, SCREEN_W, SCREEN_H, makecol( 255, 0, 255));
}

stair::~stair(){
  //dtor
}
int stair::getType(){
  return type;
}

void stair::setType(int newType){
  type=newType;
}

// Update those stairs
void stair::update( vector<stair>* allStairsCopy){
  // reset stairs
  if( y > SCREEN_H + image -> h){
    if( !is_game_done){
      x = allStairsCopy -> at(find_top_stair(stairID)).x + 30;
      y = location_y(x);
    }
    else if( is_game_done && !final_stair_placed){
      type = 1;
      final_stair_placed = true;
      x = allStairsCopy -> at(find_top_stair(stairID)).x + 30;
      y = location_y(x) - 30;
    }
  }
}

void stair::movement(){
  // Move
  x -= scrollSpeed;

  if( type == 1 || type == 2){
    y = location_y(x);
    locationOfFinal = y;
  }
  else{
    y = location_y(x - 30);
  }
}

// Draw those stairs
// YES WE CAN
void stair::draw( BITMAP *tempImage){
  // Draw stair and rectangle beside for effect
  for( int i = x + image -> w - 30; i < SCREEN_W; i+= image_brick -> w){
    draw_sprite( tempImage, image_brick, i, y + image -> h);
  }

  // Swaggin images
  if( type == 0){
    draw_sprite( tempImage, image, x, y);
  }
  else if( type == 1){
    draw_sprite( tempImage, stage_end_red, x, y);
    blit( transparency_bitmap, tempImage, 0, 0, x + stage_end_red -> w, y, SCREEN_W, SCREEN_H);
    line( tempImage, x + stage_end_red -> w - 1, y + 30, x + stage_end_red -> w - 1, SCREEN_H, makecol( 168, 148, 148));
  }
  else if( type == 2){
    draw_sprite( tempImage, stage_end_green, x, y);
    blit( transparency_bitmap, tempImage, 0, 0, x + stage_end_green -> w, y, SCREEN_W, SCREEN_H);
    line( tempImage, x + stage_end_green-> w - 1, y + 30, x + stage_end_green -> w - 1, SCREEN_H, makecol( 168, 148, 148));
  }

}

// Line y position
float stair::location_y( float oldX){
  return (SCREEN_H - ((oldX-SCREEN_W/2)/30) * 37);
}

// Line y position
int stair::find_top_stair( int stairIndex){
  // New index
  int bottomIndex = stairIndex - 1;

  // Too High? Wrap around (only happens when number is max)
  if( bottomIndex < 0){
    bottomIndex = numberStairs - 1;
  }

  return bottomIndex;
}
