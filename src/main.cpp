#include <asw/asw.h>
#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

// For state engine
#include "State.h"

using namespace std::chrono_literals;
using namespace std::chrono;
constexpr nanoseconds timestep(16ms);

// Functions
void setup();
void draw();
void update();

// FPS system
int fps = 0;
int frames_done = 0;

// State engine
StateEngine game_state;

// Setup game
void setup() {
  // Load allegro library
  asw::core::init(740, 540);
}

// Update
void update() {
  // Update core
  asw::core::update();

  // Do state logic
  game_state.update();
}

// Do state rendering
void draw() {
  SDL_RenderClear(asw::display::renderer);
  game_state.draw();
  SDL_RenderPresent(asw::display::renderer);
}

// Loop (emscripten compatibility)
#ifdef __EMSCRIPTEN__
void loop() {
  update();
  draw();
}
#endif

// Main function
auto main(int argc, char* argv[]) -> int {
  // Setup basic functionality
  setup();

  // Set the current state ID
  game_state.setNextState(StateEngine::STATE_INIT);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#else

  using clock = high_resolution_clock;
  nanoseconds lag(0ns);
  auto time_start = clock::now();

  while (!asw::input::keyboard.down[SDL_SCANCODE_ESCAPE] && !asw::core::exit &&
         game_state.getStateId() != StateEngine::STATE_EXIT) {
    auto delta_time = clock::now() - time_start;
    time_start = clock::now();
    lag += duration_cast<nanoseconds>(delta_time);

    while (lag >= timestep) {
      lag -= timestep;
      update();
    }

    draw();
    frames_done++;
  }
#endif

  return 0;
}
