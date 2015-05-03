#ifndef LOCATION_H
#define LOCATION_H

#include <allegro.h>
#include <string>

using namespace std;

// Location for map
class location{
  public:
    location(int newX, int newY, BITMAP *newImage, string newName);
    virtual ~location();

    void draw( BITMAP *tempImage);

    static BITMAP *pin_image;

    bool CheckHover();
    string getName();
  protected:
    BITMAP *image;
    int x;
    int y;
    bool hover;
    string name;
  private:
};

#endif // LOCATION_H
