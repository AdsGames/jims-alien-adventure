#include "key_manager.h"

BITMAP* key_manager::keys[255];

// Init
key_manager::key_manager(int newX, int newY){
  // Set position
  x = newX;
  y = newY;

  // Add keys
  for( int i = 0; i < 4; i++){
    key_data newKey(KEY_UP);
    key_queue.push_back(newKey);
  }

  // No keys down
  keyIsPressed = false;
}

key_manager::~key_manager(){ }

// Update
void key_manager::update(){
  // Pressing them keys
  if( key[key_queue.at(0).getValue()] && keyIsPressed == false){
    key_queue.erase( key_queue.begin());

    key_data newKey(KEY_UP);//random(KEY_LEFT, KEY_DOWN));
    key_queue.push_back(newKey);

    if( stair::scrollSpeed < stair::maxScrollSpeed)
      stair::scrollSpeed += 0.5;
  }

  // Slow stairs down
  if( stair::scrollSpeed > 0.015)
    stair::scrollSpeed -= 0.015;
  else{
    stair::scrollSpeed = 0;
  }

  // Prevents held keys
  if( keyDown())
    keyIsPressed = true;
  else
    keyIsPressed = false;
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
