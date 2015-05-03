#include "Story.h"

Story::Story()
{
  // Create buffer image
  buffer = create_bitmap( SCREEN_W, SCREEN_H);
  if(!(story_splash = load_bitmap( "images/story_splash.png", NULL))){
    abort_on_error( "Cannot find image images/story_splash.png \n Please check your files and try again");
  }

  // Temporary fonts
  FONT *f1, *f2, *f3, *f4, *f5;

  //Sets Font
  if(!(f1 = load_font(("fonts/dosis.pcx"), NULL, NULL))){
    abort_on_error( "Cannot find font fonts/dosis.png \n Please check your files and try again");
  }

  f2 = extract_font_range(f1, ' ', 'A'-1);
  f3 = extract_font_range(f1, 'A', 'Z');
  f4 = extract_font_range(f1, 'Z'+1, 'z');

  //Merge fonts
  font = merge_fonts(f4, f5 = merge_fonts(f2, f3));

  //Destroy temporary fonts
  destroy_font(f1);
  destroy_font(f2);
  destroy_font(f3);
  destroy_font(f4);
  destroy_font(f5);

  // Allow transparency
  set_alpha_blender();

  highcolor_fade_in( story_splash, 16);
}

void Story::update(){
  for( int i = 0; i < 127; i++){
    if( key[i]){
      set_next_state(STATE_MENU);
      break;
    }
  }
}

void Story::draw(){
  draw_sprite(buffer,story_splash,0,0);
  draw_sprite(screen,buffer,0,0);
}

Story::~Story(){
  // Destory Bitmaps
  destroy_bitmap( buffer);

  // Fade out
  highcolor_fade_out(16);

  // Clean up fmod
  FSOUND_Close();
}
