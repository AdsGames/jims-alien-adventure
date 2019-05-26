#include "Init.h"

#include <allegro.h>

#include "globals.h"
#include "tools.h"

Init::Init() {
  set_color_depth (32);
  set_gfx_mode (GFX_AUTODETECT_WINDOWED, 740, 540, 0, 0);
  set_window_title ("Jim's Alien Adventure");
  joystick_enabled = num_joysticks > 0;
  set_display_switch_mode(SWITCH_BACKGROUND);
}

void Init::update(StateEngine *engine) {
  setNextState (engine, StateEngine::STATE_INTRO);
}
