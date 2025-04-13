#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <asw/asw.h>
#include <array>
#include <vector>

class KeyManager {
 public:
  KeyManager() = default;

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
  std::array<asw::Texture, asw::input::NUM_KEYS> keys{nullptr};
  std::array<asw::Sample, 2> sounds{nullptr};

  // Positioning
  int x;
  int y;
};

#endif  // KEYMANAGER_H
