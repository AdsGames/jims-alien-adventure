#ifndef PLAYER_H
#define PLAYER_H

#include <allegro.h>

class player {
  public:
    player (float x, float y);
    player (const player& p);
    virtual ~player();

    void draw (BITMAP *buffer);
    void update(int frame);

    int getX();
    int getY();

    int getHeight();

  private:
    // Frame
    int frame;

    // Variables
    float x, y;

    // Images
    BITMAP *images[8];
};

#endif // PLAYER_H
