#ifndef MAP_H
#define MAP_H

#include "State.h"

#include <allegro.h>
#include <vector>

#include "location.h"

class Map : public State {
  public:
    Map();
    ~Map();

    virtual void update(StateEngine *engine) override;
    virtual void draw() override;

  private:
    // Map/GUI
    BITMAP *buffer;
    BITMAP *map_image;
    BITMAP *cursor;

    SAMPLE *music;

    std::vector<location> locations;
};

#endif // MAP_H
