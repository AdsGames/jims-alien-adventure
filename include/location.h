#ifndef LOCATION_H
#define LOCATION_H

#include <allegro.h>
#include <string>

// Location for map
class location {
  public:
    location (int x, int y, int id);
    location (const location& l);
    virtual ~location();

    void Draw (BITMAP *tempImage);

    bool Hover();

    std::string GetName();

  private:
    static BITMAP *pin_images[2];
    static BITMAP *images[6];
    static int location_count;

    static const int num_locations;

    void load_sprites();
    void unload_sprites();

    int id;
    int x, y;
};

#endif // LOCATION_H
