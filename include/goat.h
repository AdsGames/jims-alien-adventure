#ifndef GOAT_H
#define GOAT_H

#include <allegro.h>

class goat
{
  public:
    goat(float newX, float newY, float newScale, float newSpeed);
    virtual ~goat();

    // Functions
    void draw( BITMAP* tempImage);
    void update();

    // Image
    static BITMAP *goat_image;
  protected:
  private:
    // Variables
    float x, y;
    float speed;
    float scale;
};

#endif // GOAT_H
