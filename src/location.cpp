#include "location.h"
#include "tools.h"

BITMAP* location::pin_image;

// Construct
location::location(int newX, int newY, BITMAP *newImage){
  image = newImage;
  x = newX;
  y = newY;
  hover = false;
}

// De-construct
location::~location(){ }

// Draw image
void location::draw( BITMAP *tempImage){
  // Pin
  draw_trans_sprite( tempImage, pin_image, x, y);

  // Image
  if( CheckHover())
    draw_sprite( tempImage, image, mouse_x, mouse_y);
}

// Mouse is hovering
bool location::CheckHover(){
  if( collisionAny( x, x + pin_image -> w, mouse_x, mouse_x, y, y + pin_image -> h, mouse_y, mouse_y)){
    hover = true;
  }
  else{
    hover = false;
  }
  return hover;
}
