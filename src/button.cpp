#include "button.h"

using namespace std;

Button::Button( char image1[], char image2[], int newX, int newY){
  // Images
  if(!(images[0] = load_bitmap(image1, NULL))){
    abort_on_error( ("Cannot find image " + string(image1) + " \n Please check your files and try again").c_str());
  }
  if(!(images[1] = load_bitmap(image2, NULL))){
    abort_on_error( ("Cannot find image " + string(image2) + " \n Please check your files and try again").c_str());
  }

  // Size
  button_height = images[0] -> h;
  button_width = images[1] -> w;

  // Position
  x = newX;
  y = newY;
  hover = false;
}

Button::~Button(){
  destroy_bitmap( images[0]);
  destroy_bitmap( images[1]);
}

void Button::SetImages( char image1[], char image2[]){
  images[0] = load_bitmap(image1, NULL);
  images[1] = load_bitmap(image2, NULL);
}

void Button::SetHover(bool newHover){
  hover = newHover;
}

bool Button::GetHover(){
  return hover;
}

bool Button::CheckHover(){
  if( mouse_x > GetX() && mouse_x < GetX() + button_width && mouse_y > GetY() && mouse_y < GetY() + button_height)
    hover = true;
  else
    hover = false;
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
