#include "location.h"

BITMAP* location::pin_image;

// Construct
location::location(int newX, int newY, char newImage[], string newName){
  x = newX;
  y = newY;
  if(!(image = load_bitmap( newImage, NULL))){
    abort_on_error( ("Cannot find image " + (string)newImage + " \n Please check your files and try again").c_str());
  }
  name = newName;
  hover = false;
}

// De-construct
location::~location(){
  //?? WHY DONT YOUU WORK!K! destroy_bitmap( image);
}

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

// Mouse is hovering
string location::getName(){
  return name;
}
