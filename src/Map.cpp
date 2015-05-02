#include "Map.h"

Map::Map()
{
  // Init fmod
  FSOUND_Init (44100, 32, 0);

  // Create buffer image
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Load music
  if(!(music = FSOUND_Stream_Open("music/the-experiment.mp3",2, 0, 0))){
      abort_on_error( "Cannot find music music/the-experiment.mp3 \n Please check your files and try again");
  }

  // Temporary fonts
  FONT *f1, *f2, *f3, *f4, *f5;

  //Sets Font
  if(!(f1 = load_font(("fonts/arial_black.pcx"), NULL, NULL))){
    abort_on_error( "Cannot find font fonts/arial_black.png \n Please check your files and try again");
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

  FSOUND_Stream_Play(0,music);
}

void Map::update(){
}

void Map::draw(){
  // Draw background to screen
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255,255,255));

  // Intro stuff here
  textprintf_ex( buffer, font, 0, 130, makecol(255,255,255), makecol(0,0,0), "MENU!");

  // Draw Buffer
  draw_sprite( screen, buffer, 0, 0);
}

Map::~Map(){
  // Destory Bitmaps
  destroy_bitmap( buffer);

  // Fade out
  highcolor_fade_out(16);

  // Stop music
  FSOUND_Stream_Stop(music);

  // Clean up fmod
  FSOUND_Close();
}
