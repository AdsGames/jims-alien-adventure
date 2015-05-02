#include "button.h"

using namespace std;

Button::Button( BITMAP *newImage1, BITMAP *newImage2, int newX, int newY){
  // Images
  images[0] = newImage1;
  images[1] = newImage2;

  // Size
  button_height = newImage1 -> h;
  button_width = newImage1 -> w;

  // Position
  x = newX;
  y = newY;
}

Button::~Button(){

}

void Button::SetImages( char image1[], char image2[]){
  images[0]= load_bitmap(image1, NULL);
  images[1]= load_bitmap(image2, NULL);
}

void Button::SetHover(bool newHover){
  hover = newHover;
}

bool Button::GetHover(){
  return hover;
}

bool Button::CheckHover(){
  if( mouse_x > GetX() && mouse_x < GetX() + button_width && mouse_y > GetY() && mouse_y < GetY() + button_height){
    hover = true;
  }
  else{
    hover = false;
  }
  return hover;
}

void Button::SetPosition(int newX, int newY){
  x = newX;
  y = newY;
}

int Button::GetX(){
  return x;
}

int Button::GetY(){
  return y;
}

void Button::draw(BITMAP* tempBitmap){
  if(CheckHover())
    draw_sprite( tempBitmap, images[1], x, y);
  else
    draw_sprite( tempBitmap, images[0], x, y);
}
