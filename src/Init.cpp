#include "Init.h"

Init::Init()
{
  // Set window title
  set_window_title("Error");

  int width;
  int height;
  //get_desktop_resolution(&width,&height);

  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 960, 540, 0, 0);

  set_window_title("Tojam 10!");

  if(num_joysticks>0)
    input_mode=true;
}

void Init::update()
{
  // Change to splash screen
  set_next_state(STATE_GAME);
}

void Init::draw()
{

}

Init::~Init()
{

}
