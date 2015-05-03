#ifndef BUTTON_H
#define BUTTON_H

#include <allegro.h>
#include "tools.h"

using namespace std;

class Button{
  public:
    Button( char image1[], char image2[], int newX, int newY);
    ~Button();

    void SetImages( char image1[], char image2[]);

    void SetHover(bool newHover);
    bool GetHover();

    void draw(BITMAP* tempBitmap);

    void SetPosition( int newX, int newY);

    void SetType(int newType);
    void SetValue(int newValue);

    bool CheckHover();

    int GetX();
    int GetY();

  private:
    int button_height;
    int button_width;

    int x;
    int y;

    bool hover;

    BITMAP *images[2];
};

#endif

