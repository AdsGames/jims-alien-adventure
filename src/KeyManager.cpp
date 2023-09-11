#include "KeyManager.h"

#include "tools.h"

// Init
KeyManager::KeyManager(int x, int y) {
  // Set position
  this->x = x;
  this->y = y;

  // Add keys
  for (int i = 0; i < 4; i++)
    pushKey();

  // Nullify keys
  for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
    keys[i] = nullptr;
  }

  // Load images
  keys[SDL_SCANCODE_UP] =
      asw::assets::loadTexture("assets/images/keys/key_up.png");
  keys[SDL_SCANCODE_DOWN] =
      asw::assets::loadTexture("assets/images/keys/key_down.png");
  keys[SDL_SCANCODE_LEFT] =
      asw::assets::loadTexture("assets/images/keys/key_left.png");
  keys[SDL_SCANCODE_RIGHT] =
      asw::assets::loadTexture("assets/images/keys/key_right.png");
  keys[0] = asw::assets::loadTexture("assets/images/keys/joy_a.png");
  keys[3] = asw::assets::loadTexture("assets/images/keys/joy_y.png");
  keys[2] = asw::assets::loadTexture("assets/images/keys/joy_x.png");
  keys[1] = asw::assets::loadTexture("assets/images/keys/joy_b.png");

  sounds[0] = asw::assets::loadSample("assets/sounds/trip.wav");
  sounds[1] = asw::assets::loadSample("assets/sounds/ping.wav");
}

// Push key
void KeyManager::pushKey() {
  // num_joysticks > 0 ? random(0, 3) : TODO
  int value = random(SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP);
  key_queue.push_back(value);
}

// Pop key
void KeyManager::popKey() {
  key_queue.erase(key_queue.begin());
}

// Update
int KeyManager::update() {
  int result = 0;

  // Got a correct letter
  if (key_queue.size() > 0 && asw::input::keyboard.anyPressed) {
    if (asw::input::keyboard.pressed[key_queue.at(0)]) {
      asw::sound::play(sounds[1], 255, 125, 0);
      popKey();
      pushKey();
      result = 1;
    } else {
      asw::sound::play(sounds[0], 255, 125, 0);
      result = -1;
    }
  }

  return result;
}

// Draw
void KeyManager::draw() {
  // Background
  asw::draw::rectFill(x + 15, y + 75, 209 - 95, 7 + (key_queue.size() * 90),
                      asw::util::makeColor(155, 155, 155));

  // Draw keys
  for (unsigned int i = 0; i < key_queue.size(); i++) {
    asw::draw::sprite(keys[key_queue.at(i)], x + 20, -(i * 90) + y + 350);
  }
}
