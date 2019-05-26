#ifndef GOAT_H
#define GOAT_H

#include <allegro.h>

class goat {
  public:
    goat (float x, float y, float scale, float speed);
    goat (const goat& g);
    virtual ~goat();

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
