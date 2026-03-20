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
  app.register_scene<Init>(States::Init, app);
  app.register_scene<Intro>(States::Intro, app);
  app.register_scene<Menu>(States::Menu, app);
  app.register_scene<Story>(States::Story, app);
  app.register_scene<Game>(States::Game, app);
  app.register_scene<Map>(States::Map, app);
  app.set_next_scene(States::Init);

  app.start();

  return 0;
}
