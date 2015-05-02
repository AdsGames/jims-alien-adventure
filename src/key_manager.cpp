#include "key_manager.h"
#include "globals.h"

BITMAP* key_manager::keys[255];

// Init
key_manager::key_manager(int newX, int newY){
  // Set position
  x = newX;
  y = newY;

  // Add keys
  for( int i = 0; i < 4; i++){
    if(!input_mode){
        key_data newKey(KEY_UP);
        key_queue.push_back(newKey);
    }
    if(input_mode){
      key_data newKey(0);
      key_queue.push_back(newKey);
    }

  }

  // No keys down
  keyIsPressed = false;
}

key_manager::~key_manager(){ }

// Update
void key_manager::update(){
  // Pressing them keys
  if(!input_mode){
    if( key[key_queue.at(0).getValue()] && keyIsPressed == false){
      key_queue.erase( key_queue.begin());

<<<<<<< HEAD
      key_data newKey(random(KEY_LEFT, KEY_DOWN));
      key_queue.push_back(newKey);
=======
    key_data newKey(KEY_UP);//random(KEY_LEFT, KEY_DOWN));
    key_queue.push_back(newKey);
>>>>>>> 4d7dbfb873b339bf811dae82cc0aa728d37cca82

      if( stair::scrollSpeed < stair::maxScrollSpeed)
        stair::scrollSpeed += 0.5;
      }
      else if( keyDown() && keyIsPressed == false){
        stair::scrollSpeed = 0;
    }
  }

  if(input_mode){
    if( joy[0].button[key_queue.at(0).getValue()].b && buttonIsPressed == false){
      key_queue.erase( key_queue.begin());

      key_data newKey(random(0,3));
      key_queue.push_back(newKey);

      if( stair::scrollSpeed < stair::maxScrollSpeed)
        stair::scrollSpeed += 0.5;
      }
      else if( buttonDown() && buttonIsPressed == false){
        stair::scrollSpeed = 0;
    }
  }

  // Prevents held keys
  if(!input_mode){
    if( keyDown())
    keyIsPressed = true;
  else
    keyIsPressed = false;
  }
  if(input_mode){
    if( buttonDown())
    buttonIsPressed = true;
  else
    buttonIsPressed = false;
  }

  // Slow stairs down
  if( stair::scrollSpeed > 0.01)
    stair::scrollSpeed -= 0.01;
  else{
    stair::scrollSpeed = 0;
  }
}

// Draw
void key_manager::draw( BITMAP *tempImage){
  // Background
  rectfill( tempImage, x, y, x + key_queue.size() * 120, y + 100, makecol( 155, 155, 155));

  // Draw keys
  for( unsigned int i = 0; i < key_queue.size(); i++){
    set_trans_blender(255, 255, 255, 255 - ((255/4) * i));
    draw_trans_sprite( tempImage, keys[key_queue.at(i).getValue()], i * 120 + x + 5, y + 5);
  }
}

// Key down
bool key_manager::keyDown(){
  for( int i = 0; i < 127; i++){
    if( key[i])
      return true;
  }
  return false;
}

// Joystick
bool key_manager::buttonDown(){
  for( int i = 0; i < 10; i++){
    if( joy[0].button[i].b)
      return true;
  }
  return false;
}
