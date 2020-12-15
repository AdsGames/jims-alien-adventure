#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <allegro.h>
#include <vector>

class KeyManager {
 public:
  KeyManager(int x, int y);
  virtual ~KeyManager();

  // Functions
  void draw(BITMAP* tempImage);
  int update();

 private:
  // All keys for queue
  std::vector<int> key_queue;

  // Push new key
  void pushKey();
  void popKey();

  // Images and sounds
  BITMAP* keys[KEY_MAX];
  SAMPLE* sounds[2];

  // Positioning
  int x;
  int y;

  // Any key?
  bool past_frame_input;
};

#endif  // KEYMANAGER_H
