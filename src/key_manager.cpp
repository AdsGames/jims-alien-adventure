#include "key_manager.h"

BITMAP* key_manager::keys[255];

// Init
key_manager::key_manager(int newX, int newY){
  // Set position
  x = newX;
  y = newY;

  // Add keys
  for( int i = 0; i < 10; i++){
    key_data newKey(KEY_UP);
    key_queue.push_back(newKey);
  }
}

key_manager::~key_manager(){ }

// Update
void key_manager::update(){
  // Pressing them keys
  if( key[key_queue.at(0).getValue()]){
    key_queue.erase( key_queue.begin());

    key_data newKey(random(KEY_LEFT, KEY_DOWN));
    key_queue.push_back(newKey);
  }
}

// Draw
void key_manager::draw( BITMAP *tempImage){
  // Draw keys
  for( unsigned int i = 0; i < key_queue.size(); i++){
    draw_sprite( tempImage, keys[key_queue.at(i).getValue()],i * 80 + x, y);
  }
}
