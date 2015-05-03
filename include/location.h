#ifndef LOCATION_H
#define LOCATION_H

#include "allegro.h"

// Location for map
class location{
  public:
    location(int newX, int newY, BITMAP *newImage);
    virtual ~location();

    void draw( BITMAP *tempImage);

    static BITMAP *pin_image;

    bool CheckHover();
  protected:
    BITMAP *image;
    int x;
    int y;
    bool hover;
  private:
};

#endif // LOCATION_H
