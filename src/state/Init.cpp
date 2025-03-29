#include "./Init.h"

#include <asw/asw.h>
#include <ctime>

#include "../LevelData.h"
#include "../tools.h"

void Init::init() {
  asw::display::setTitle("Jim's Alien Adventure");
  asw::display::setIcon("assets/images/icon.png");
}

void Init::update(float deltaTime) {
  Scene::update(deltaTime);

  sceneManager.setNextScene(States::Intro);
}
