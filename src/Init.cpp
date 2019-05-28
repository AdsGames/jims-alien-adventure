#include "Init.h"

#include <allegro.h>

#include "tools.h"
#include "LevelData.h"

Init::Init() {
  set_window_title ("Jim's Alien Adventure");
  set_display_switch_mode(SWITCH_BACKGROUND);

  srand(time(NULL));
  set_alpha_blender();
}

void Init::update(StateEngine *engine) {
  setNextState (engine, StateEngine::STATE_INTRO);
}

void Init::draw(BITMAP *buffer) {
  clear_to_color(buffer, 0xFFFFFF);
}
