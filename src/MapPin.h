#ifndef MAP_PIN_H
#define MAP_PIN_H

#include <allegro.h>
#include <string>

// Location for map
class MapPin {
  public:
    MapPin (int x, int y, std::string &folder, bool completed, int id);
    virtual ~MapPin();

    void Draw (BITMAP *tempImage);
    bool Hover();
    int GetID();

  private:
    BITMAP *image;
    static BITMAP *pin_images[2];
    static int pin_count;

    void load_sprites();
    void unload_sprites();

    int id;
    int x, y;
    bool completed;
};

#endif // MAP_PIN_H
