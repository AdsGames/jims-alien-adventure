#include "Init.h"

Init::Init()
{
  // Set window title
  set_window_title("Error");

  int width;
  int height;
  //get_desktop_resolution(&width,&height);

  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 740, 540, 0, 0);

  set_window_title("Jim: Alien Adventures");

  if(num_joysticks>0)
    input_mode=true;
}

void Init::update()
{
  // Change to splash screen
  set_next_state(STATE_MENU);
}

void Init::draw()
{

}

Init::~Init()
{

}
