#include "key_manager.h"

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

}

// Draw
void key_manager::draw( BITMAP *tempImage){
  // Draw keys
  for( unsigned int i = 0; i < key_queue.size(); i++){
    rectfill( tempImage, i * 40 + x, y, i * 40 + 30, y + 30, makecol( 255,0,0));
  }
}
