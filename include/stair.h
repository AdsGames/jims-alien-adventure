#ifndef STAIR_H
#define STAIR_H

#include <vector>
#include <allegro.h>

using namespace std;

class stair
{
  public:
    stair(float newX, float newY, int newType);
    virtual ~stair();

    // FUNctions
    void update( vector<stair>* allStairsCopy);
    void movement();
    void draw( BITMAP *tempImage);

    static float location_y( float oldX);
    int find_top_stair( int stairIndex);

    // Static members
    static int numberStairs;
    static float locationOfFinal;
    static float scrollSpeed;
    static bool final_stair_placed;
    static BITMAP* image;
    static BITMAP* image_brick;
    static BITMAP* stage_end_red;

    static const int maxScrollSpeed;
  protected:
  private:
    float x;
    float y;

    int type;
    int stairID;

    BITMAP* transparency_bitmap;
};

#endif // STAIR_H
