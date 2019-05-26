#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#include <allegro.h>
#include <vector>

#include "key_data.h"

class key_manager {
  public:
    key_manager (int newX, int newY);
    virtual ~key_manager();

    // All keys
    static BITMAP *keys[255];
    static SAMPLE *sounds[5];

    // Functions
    void draw (BITMAP *tempImage);
    void update();

    bool keyDown();
    bool buttonDown();
  protected:
  private:
    // All keys for queue
    std::vector<key_data> key_queue;

    // Positioning
    int x;
    int y;

    // Any key?
    bool buttonPressedCombo();
    bool keyPressedCombo();
    bool buttonIsPressed;
    bool keyIsPressed;
};

#endif // KEY_MANAGER_H
