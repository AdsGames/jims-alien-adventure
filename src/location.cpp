#include "location.h"


BITMAP* location::pin_image;
BITMAP* location::pin_grey_image;

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
  if(name=="cn_tower" && !beaten_levels[0])draw_trans_sprite( tempImage, pin_image, x, y);
  if(name=="pyramids" && !beaten_levels[1])draw_trans_sprite( tempImage, pin_image, x, y);
  if(name=="statue_of_liberty" && !beaten_levels[2])draw_trans_sprite( tempImage, pin_image, x, y);
  if(name=="stone_henge" && !beaten_levels[3])draw_trans_sprite( tempImage, pin_image, x, y);
  if(name=="taj_mahal" && !beaten_levels[4])draw_trans_sprite( tempImage, pin_image, x, y);
  if(name=="wall_of_china" && !beaten_levels[6])draw_trans_sprite( tempImage, pin_image, x, y);

  if(name=="cn_tower" && beaten_levels[0])draw_trans_sprite( tempImage, pin_grey_image, x, y);
  if(name=="pyramids" && beaten_levels[1])draw_trans_sprite( tempImage, pin_grey_image, x, y);
  if(name=="statue_of_liberty" && beaten_levels[2])draw_trans_sprite( tempImage, pin_grey_image, x, y);
  if(name=="stone_henge" && beaten_levels[3])draw_trans_sprite( tempImage, pin_grey_image, x, y);
  if(name=="taj_mahal" && beaten_levels[4])draw_trans_sprite( tempImage, pin_grey_image, x, y);
  if(name=="wall_of_china" && beaten_levels[6])draw_trans_sprite( tempImage, pin_grey_image, x, y);

  // Image
  if( CheckHover())
    draw_sprite( tempImage, image, mouse_x, mouse_y);
}

// Mouse is hovering
bool location::CheckHover(){
  if( collisionAny( x, x + pin_image -> w, mouse_x, mouse_x, y, y + pin_image -> h, mouse_y, mouse_y))
    hover = true;
  else
    hover = false;
  return hover;
}

// Mouse is hovering
string location::getName(){
  return name;
}
