#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#include <allegro.h>
#include <vector>

class key_manager {
  public:
    key_manager (int x, int y);
    virtual ~key_manager();

    // Functions
    void draw (BITMAP *tempImage);
    int update();

    bool keyDown();
    bool buttonDown();

  private:
    // All keys for queue
    std::vector<int> key_queue;

    // Push new key
    void pushKey();
    void popKey();

    // Images and sounds
    BITMAP *keys[127];
    SAMPLE *sounds[5];

    // Positioning
    int x;
    int y;

    // Any key?
    bool past_frame_input;
};

#endif // KEY_MANAGER_H
