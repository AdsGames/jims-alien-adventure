#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <asw/asw.h>
#include <vector>

class KeyManager {
 public:
  KeyManager(int x, int y);

  // Functions
  void draw();
  int update();

 private:
  // All keys for queue
  std::vector<int> key_queue;

  // Push new key
  void pushKey();
  void popKey();

  // Images and sounds
  asw::Texture keys[SDL_NUM_SCANCODES];
  asw::Sample sounds[2];

  // Positioning
  int x;
  int y;
};

#endif  // KEYMANAGER_H
