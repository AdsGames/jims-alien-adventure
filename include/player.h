#ifndef PLAYER_H
#define PLAYER_H

#include <allegro.h>

class player
{
  public:
    player(float newX, float newY, BITMAP *newImage);
    virtual ~player();

    void draw( BITMAP *tempImage);
    void update();
  protected:
  private:
    // Images
    BITMAP *image;

    // Variables
    float x;
    float y;
};

#endif // PLAYER_H
