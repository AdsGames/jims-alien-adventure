#ifndef GOAT_H
#define GOAT_H

#include <allegro.h>

class Goat {
  public:
    Goat (float x, float y, float scale, float speed);
    Goat (const Goat& g);
    virtual ~Goat();

    // Functions
    void update();
    void fall (float speed);
    bool offScreen();
    void draw (BITMAP *buffer);

  private:
    // Variables
    float x, y;
    float speed;
    float scale;

    // Images
    static BITMAP *goat_image[2];
    static int goat_count;

    void load_sprites();
    void unload_sprites();

};

#endif // GOAT_H
