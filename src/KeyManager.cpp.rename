#include "key_manager.h"

#include "globals.h"
#include "tools.h"
#include "stair.h"

BITMAP *key_manager::keys[255];
SAMPLE *key_manager::sounds[5];

// Init
key_manager::key_manager (int newX, int newY) {
  // Set position
  x = newX;
  y = newY;

  // Add keys
  for (int i = 0; i < 4; i++) {
    if (!joystick_enabled) {
      key_data newKey (random (KEY_LEFT, KEY_DOWN));
      key_queue.push_back (newKey);
    }

    if (joystick_enabled) {
      key_data newKey (random (0, 3));
      key_queue.push_back (newKey);
    }
  }

  // No keys down
  keyIsPressed = false;
}

key_manager::~key_manager() {
  key_queue.clear();
}

// Update
void key_manager::update() {
  // Pressing them keys
  // You haven't won
  if (!switch_flicked) {
    // Got a correct letter
    if ((key_queue.size() > 0) &&
        ((!joystick_enabled &&
          key[key_queue.at (0).getValue()] &&
          !keyIsPressed) ||
         (joystick_enabled &&
          joy[0].button[key_queue.at (0).getValue()].b &&
          !buttonIsPressed))) {

      // Nice sound
      play_sample (sounds[1], 255, 125, 1000, 0);
      key_queue.erase (key_queue.begin());

      // Add key to queue
      if (joystick_enabled) {
        key_data newKey (random (0, 3));
        key_queue.push_back (newKey);
      }
      else {
        key_data newKey (random (KEY_LEFT, KEY_DOWN));
        key_queue.push_back (newKey);
      }

      // Increase speed
      if (stair::scrollSpeed < stair::maxScrollSpeed) {
        stair::scrollSpeed += 0.8;
      }
    }
    else if ((keyDown() && keyIsPressed == false) || (buttonDown() && buttonIsPressed == false)) {
      if (stair::scrollSpeed > 0) {
        stair::scrollSpeed /= 4;
      }

      play_sample (sounds[0], 255, 125, 1000, 0);
    }
  }
  // Stop
  else {
    stair::scrollSpeed = 0;
  }

  // Prevents held keys
  if (!joystick_enabled) {
    keyIsPressed = keyDown();
  }

  if (joystick_enabled) {
    buttonIsPressed = buttonDown();
  }

  // Slow stairs down
  if (stair::scrollSpeed > 0.01) {
    stair::scrollSpeed -= 0.02;
  }
  else {
    stair::scrollSpeed = 0;
  }
}

// Draw
void key_manager::draw (BITMAP *tempImage) {
  if (!switch_flicked) {
    // Background
    rectfill (tempImage, x + 15, y + 75, x   + 209 - 80, y + 83 + (key_queue.size() * 90), makecol (155, 155, 155));

    // Draw keys
    for (unsigned int i = 0; i < key_queue.size(); i++) {
      set_trans_blender (255, 255, 255, 255 - ((255 / 4) * i));
      draw_trans_sprite (tempImage, keys[key_queue.at (i).getValue()], x + 20,  - (i * 90) + y + 350);
    }
  }
}

//Arrow keys pressed
//EPIC WOMBO COMBOS
bool key_manager::keyPressedCombo() {
  if (key[KEY_UP] && key[KEY_DOWN] && key[KEY_LEFT] && key[KEY_RIGHT]) {
    return true;
  }

  return false;
}

//Button keys pressed
//EPIC WOMBO COMBOS
bool key_manager::buttonPressedCombo() {
  if (joy[0].button[0].b && joy[0].button[1].b && joy[0].button[2].b && joy[0].button[3].b) {
    return true;
  }

  return false;
}


// Key down
bool key_manager::keyDown() {
  for (int i = 0; i < 127; i++) {
    if (key[i]) {
      return true;
    }
  }

  return false;
}

// Joystick
bool key_manager::buttonDown() {
  for (int i = 0; i < 10; i++) {
    if (joy[0].button[i].b) {
      return true;
    }
  }

  return false;
}
