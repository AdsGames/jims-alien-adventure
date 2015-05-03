#include "Story.h"

Story::Story()
{
  // Create buffer image
  buffer = create_bitmap( SCREEN_W, SCREEN_H);
  if(!(story_splash = load_bitmap( "images/story_splash.png", NULL))){
    abort_on_error( "Cannot find image images/story_splash.png \n Please check your files and try again");
  }

  // Quick splash
  highcolor_fade_in( story_splash, 32);
}

// Update
void Story::update(){
  for( int i = 0; i < 127; i++){
    if( key[i]){
      set_next_state(STATE_MENU);
      break;
    }
  }
}

// Draw
void Story::draw(){
  // Yay draw
  draw_sprite(buffer,story_splash,0,0);
  draw_sprite(screen,buffer,0,0);
}

// Destroy
Story::~Story(){
  // Destory Bitmaps
  destroy_bitmap(buffer);
  destroy_bitmap(story_splash);

  // Fade out
  highcolor_fade_out(32);
}
