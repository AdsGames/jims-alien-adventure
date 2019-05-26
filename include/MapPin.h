#ifndef MAP_PIN_H
#define MAP_PIN_H

#include <allegro.h>
#include <string>

// Location for map
class MapPin {
  public:
    MapPin (int x, int y, int id);
    virtual ~MapPin();

    void Draw (BITMAP *tempImage);
    bool Hover();
    int GetID();

  private:
    BITMAP *image;
    static BITMAP *pin_images[2];
    static int location_count;

    static const int num_locations;

    void load_sprites();
    void unload_sprites();

    int id;
    int x, y;
};

#endif // MAP_PIN_H
