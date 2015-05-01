#include "Intro.h"
#include "tools.h"

Intro::Intro()
{
  // Buffer
  buffer = create_bitmap( SCREEN_W, SCREEN_H);
}

void Intro::update(){
}

void Intro::draw(){
  // Fade in
  //highcolor_fade_in( IMAGE, 32);

  // Background
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_W, makecol( 255, 255, 255));

  // Intro stuff here
  textprintf_ex( buffer, font, 0, 130, makecol(255,255,255), makecol(0,0,0), "INTRO!");

  // Draw Buffer
  draw_sprite( screen, buffer, 0, 0);

  // Wait
  rest( 2000);

  // Fade out
  highcolor_fade_out( 64);

  // Wait 2 seconds then go to the menu
  set_next_state(STATE_MENU);
}

Intro::~Intro()
{
  // Clear memory
  destroy_bitmap( buffer);
}
