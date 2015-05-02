#ifndef PLAYER_H
#define PLAYER_H

#include <allegro.h>
#include "stair.h"

class player
{
  public:
    player(float newX, float newY);
    virtual ~player();

    void draw( BITMAP *tempImage);
    void update();

    // Images
    static BITMAP *image[7];
    static int animation_frame;
  protected:
  private:
    // Variables
    float x;
    float y;
};

#endif // PLAYER_H
