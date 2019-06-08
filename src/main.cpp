#include <allegro.h>

#include "State.h"

// State engine
StateEngine game_state;

// Buffer
BITMAP *buffer;

// Close button
volatile int close_button_pressed = FALSE;

// FPS System
volatile int ticks = 0;
const int updates_per_second = 60;
volatile int game_time = 0;
int frames_done = 0;
int fps = 0;
int old_time = 0;

void ticker() {
  ticks++;
}
END_OF_FUNCTION (ticker)

void game_time_ticker() {
  game_time++;
}
END_OF_FUNCTION (ticker)

void close_button_handler (void) {
  close_button_pressed = TRUE;
}
END_OF_FUNCTION (close_button_handler)


// Setup game
void setup() {
  // Load allegro library
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse();
  install_joystick (JOY_TYPE_AUTODETECT);
  install_sound (DIGI_AUTODETECT, MIDI_AUTODETECT, ".");

  // Setup for FPS system
  LOCK_VARIABLE (ticks);
  LOCK_FUNCTION (ticker);
  install_int_ex (ticker, BPS_TO_TIMER (updates_per_second));

  LOCK_VARIABLE (game_time);
  LOCK_FUNCTION (game_time_ticker);
  install_int_ex (game_time_ticker, BPS_TO_TIMER (10));

  // Close button
  LOCK_FUNCTION (close_button_handler);
  set_close_button_callback (close_button_handler);

  // Set up screen
  set_color_depth (32);
  set_gfx_mode (GFX_AUTODETECT_WINDOWED, 740, 540, 0, 0);

  buffer = create_bitmap(SCREEN_W, SCREEN_H);
}

// Update
void update() {
  //Do state logic
  game_state.update();

  // Handle exit
  if (game_state.getStateId() == StateEngine::STATE_EXIT)
    close_button_pressed = true;
}

//Do state rendering
void draw() {
  game_state.draw(buffer);
  stretch_sprite(screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
}

//Main function*/
int main() {
  // Setup basic functionality
  setup();

  //Set the current state ID
  game_state.setNextState(StateEngine::STATE_INIT);

  while (!key[KEY_ESC] && !close_button_pressed) {
    while (ticks == 0) {
      rest (1);
    }

    while (ticks > 0) {
      int old_ticks = ticks;

      update();

      ticks--;

      if (old_ticks <= ticks) {
        break;
      }
    }

    if (game_time - old_time >= 10) {
      fps = frames_done;
      frames_done = 0;
      old_time = game_time;
    }

    draw();
    frames_done++;
  }

  return 0;
}
END_OF_MAIN()
