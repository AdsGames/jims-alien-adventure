#ifndef MAP_H
#define MAP_H

#include "State.h"

#include <allegro.h>
#include <vector>

#include "LevelData.h"
#include "MapPin.h"

class Map : public State {
 public:
  Map();
  ~Map();

  virtual void update(StateEngine* engine) override;
  virtual void draw(BITMAP* buffer) override;

 private:
  // Map/GUI
  BITMAP* map_image;
  BITMAP* cursor;

  SAMPLE* music;

  std::vector<MapPin*> pins;
};

#endif  // MAP_H
