#ifndef STAIR_H
#define STAIR_H

#include <vector>
#include <allegro.h>

#define IMG_BRICK 0
#define IMG_STAIRS 1
#define IMG_TOP_RED 2
#define IMG_TOP_GREEN 3

class Stair {
  public:
    Stair (float newX, float newY, int newType);
    Stair (const Stair& s);
    virtual ~Stair();

    int getType();
    void setType (int newType);

    // FUNctions
    void update (std::vector<Stair> *allStairsCopy);
    void movement();
    void draw (BITMAP *buffer);

    static float location_y (float last_x);
    int find_top_stair (int index);

    // Static members
    static int numberStairs;
    static float locationOfFinal;
    static float scrollSpeed;
    static bool final_stair_placed;
    static const int maxScrollSpeed;

  private:
    float x;
    float y;

    int type;
    int stairID;

    // Images
    BITMAP *transparency_bitmap;

    static BITMAP *images[4];

    static int stair_count;

    void load_sprites();
    void unload_sprites();
};

#endif // STAIR_H
