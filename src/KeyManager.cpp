#include "KeyManager.h"

#include "tools.h"

// Init
KeyManager::KeyManager (int x, int y) {
  // Set position
  this -> x = x;
  this -> y = y;

  // Add keys
  for (int i = 0; i < 4; i++)
    pushKey();

  // No keys down
  past_frame_input = false;

  // Load images
  keys[KEY_UP] = load_png_ex("images/keys/key_up.png");
  keys[KEY_DOWN] = load_png_ex("images/keys/key_down.png");
  keys[KEY_LEFT] = load_png_ex("images/keys/key_left.png");
  keys[KEY_RIGHT] = load_png_ex("images/keys/key_right.png");
  keys[0] = load_png_ex("images/keys/joy_a.png");
  keys[3] = load_png_ex("images/keys/joy_y.png");
  keys[2] = load_png_ex("images/keys/joy_x.png");
  keys[1] = load_png_ex("images/keys/joy_b.png");

  sounds[0] = load_sample_ex ("sounds/trip.wav");
  sounds[1] = load_sample_ex ("sounds/ping.wav");
}

KeyManager::~KeyManager() {
  destroy_bitmap(keys[KEY_UP]);
  destroy_bitmap(keys[KEY_DOWN]);
  destroy_bitmap(keys[KEY_LEFT]);
  destroy_bitmap(keys[KEY_RIGHT]);
  destroy_bitmap(keys[0]);
  destroy_bitmap(keys[1]);
  destroy_bitmap(keys[2]);
  destroy_bitmap(keys[3]);

  destroy_sample(sounds[0]);
  destroy_sample(sounds[1]);
}

// Push key
void KeyManager::pushKey() {
  int value = num_joysticks > 0 ? random (0, 3) : random (KEY_LEFT, KEY_DOWN);
  key_queue.push_back (value);
}

// Pop key
void KeyManager::popKey() {
  key_queue.erase (key_queue.begin());
}

// Update
// Return  0 nothing pressed
//         1 success
//        -1 failure
int KeyManager::update() {
  int result = 0;

  // Got a correct letter
  if (key_queue.size() > 0 && !past_frame_input && (button_down() || key_down())) {
    if (key[key_queue.at(0)] || joy[0].button[key_queue.at(0)].b) {
      play_sample (sounds[1], 255, 125, 1000, 0);
      popKey();
      pushKey();
      result = 1;
    }
    else {
      play_sample (sounds[0], 255, 125, 1000, 0);
      result = -1;
    }
  }

  // Prevents held keys
  past_frame_input = (num_joysticks > 0) ? button_down() : key_down();

  return result;
}

// Draw
void KeyManager::draw (BITMAP *tempImage) {
  // Background
  rectfill (tempImage, x + 15, y + 75, x   + 209 - 80, y + 83 + (key_queue.size() * 90), makecol (155, 155, 155));

  // Draw keys
  for (unsigned int i = 0; i < key_queue.size(); i++) {
    set_trans_blender (255, 255, 255, 255 - ((255 / 4) * i));
    draw_trans_sprite (tempImage, keys[key_queue.at(i)], x + 20,  - (i * 90) + y + 350);
  }
}
