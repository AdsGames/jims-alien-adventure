#include "Init.h"

#include <asw/asw.h>
#include <time.h>

#include "LevelData.h"
#include "tools.h"

Init::Init() {
  asw::display::setTitle("Jim's Alien Adventure");
  asw::display::setIcon("assets/images/icon.png");
  srand(time(nullptr));
}

void Init::update(StateEngine* engine) {
  setNextState(engine, StateEngine::STATE_INTRO);
}

void Init::draw() {}
