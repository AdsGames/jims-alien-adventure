#include <asw/asw.h>

#include "./state/Game.h"
#include "./state/Init.h"
#include "./state/Intro.h"
#include "./state/Map.h"
#include "./state/Menu.h"
#include "./state/States.h"
#include "./state/Story.h"

// Main function
auto main() -> int {
  // Setup basic functionality
  asw::core::init(740, 540);

  // Set the current state ID
  asw::scene::SceneManager<States> app;
  app.registerScene<Init>(States::Init, app);
  app.registerScene<Intro>(States::Intro, app);
  app.registerScene<Menu>(States::Menu, app);
  app.registerScene<Story>(States::Story, app);
  app.registerScene<Game>(States::Game, app);
  app.registerScene<Map>(States::Map, app);
  app.setNextScene(States::Init);

  app.start();

  return 0;
}
