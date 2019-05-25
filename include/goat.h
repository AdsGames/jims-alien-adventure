#ifndef GOAT_H
#define GOAT_H

#include <allegro.h>
#include "tools.h"
#include "globals.h"

class goat {
  public:
    goat (float newX, float newY, float newScale, float newSpeed);
    virtual ~goat();

    // Functions
    void draw (BITMAP *tempImage);
    void update();
    void fall (float newSpeed);
    bool kill();

    // Image
    static BITMAP *goat_image[2];
  protected:
  private:
    // Variables
    float x, y;
    float speed;
    float scale;
    bool offScreen;

};

#endif // GOAT_H
