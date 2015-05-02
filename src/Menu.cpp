#include "Menu.h"

Menu::Menu()
{
  // Init fmod
  FSOUND_Init (44100, 32, 0);

  // Create buffer image
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Load music
  if(!(music = FSOUND_Stream_Open("music/JAA-Theme.mp3",2, 0, 0))){
      abort_on_error( "Cannot find music music/JAA-Theme.mp3 \n Please check your files and try again");
  }

  // Load images
  if(!(background = load_bitmap("images/menu/menu.png", NULL))){
      abort_on_error( "Cannot find image images/menu/menu.png \n Please check your files and try again");
  }
  if(!(title = load_bitmap("images/menu/title.png", NULL))){
      abort_on_error( "Cannot find image images/menu/title.png \n Please check your files and try again");
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

  // Variable set
  title_y = - title -> h;

  FSOUND_Stream_Play(0,music);
}

void Menu::update(){
  // Drop title
  if( title_y < 150)
    title_y += (150 - title_y)/100;

}

void Menu::draw(){
  // Draw background to screen
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255,255,255));
  draw_sprite( buffer, background, 0, 0);

  // Title
  draw_trans_sprite( buffer, title, 100, title_y);

  // Intro stuff here
  textprintf_ex( buffer, font, 0, 100, makecol(255,255,255), makecol(0,0,0), "MENU!");

  // Draw Buffer
  draw_sprite( screen, buffer, 0, 0);
}

Menu::~Menu(){
  // Destory Bitmaps
  destroy_bitmap( buffer);

  // Fade out
  highcolor_fade_out(16);

  // Stop music
  FSOUND_Stream_Stop(music);

  // Clean up fmod
  FSOUND_Close();
}
