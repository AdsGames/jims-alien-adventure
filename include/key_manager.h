#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

#include <vector>
#include <allegro.h>
#include "key_data.h"

using namespace std;

class key_manager
{
  public:
    key_manager(int newX, int newY);
    virtual ~key_manager();

    // All keys
    static BITMAP* keys[255];

    // Functions
    void draw( BITMAP *tempImage);
    void update();
  protected:
  private:
    // All keys for queue
    vector<key_data> key_queue;

    // Positioning
    int x;
    int y;
};

#endif // KEY_MANAGER_H
