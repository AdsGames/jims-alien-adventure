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
  if(!input_mode && !switch_flicked){
    if( key[key_queue.at(0).getValue()] && keyIsPressed == false){
      key_queue.erase( key_queue.begin());

      key_data newKey(random(KEY_LEFT, KEY_DOWN));
      key_queue.push_back(newKey);


      if( stair::scrollSpeed < stair::maxScrollSpeed)
        stair::scrollSpeed += 0.5;
      }
      else if( keyDown() && keyIsPressed == false){
        stair::scrollSpeed = 0;
    }
  }

  if(input_mode && !switch_flicked){
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
  rectfill( tempImage, x+395, y+75, x   +509, y +83+ (key_queue.size() * 90), makecol( 155, 155, 155));

  // Draw keys
  for( unsigned int i = 0; i < key_queue.size(); i++){
    set_trans_blender(255, 255, 255, 255 - ((255/4) * i));
    draw_trans_sprite( tempImage, keys[key_queue.at(i).getValue()], x + 400,  -(i * 90)+y + 350);
  }
}

//Arrow keys pressed
//EPIC WOMBO COMBOS
bool key_manager::keyPressedCombo(){
  if( key[KEY_UP] && key[KEY_DOWN] && key[KEY_LEFT]  && key[KEY_RIGHT] )
      return true;

  return false;
}

//Button keys pressed
//EPIC WOMBO COMBOS
bool key_manager::buttonPressedCombo(){
  if( joy[0].button[0].b && joy[0].button[1].b && joy[0].button[2].b && joy[0].button[3].b)
      return true;

  return false;
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
