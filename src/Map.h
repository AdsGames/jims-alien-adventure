#ifndef MAP_H
#define MAP_H

#include "State.h"

#include <asw/asw.h>
#include <vector>

#include "LevelData.h"
#include "MapPin.h"

class Map : public State {
 public:
  Map();

  virtual void update(StateEngine* engine) override;
  virtual void draw() override;

 private:
  // Map/GUI
  asw::Texture map_image;
  asw::Texture cursor;

  asw::Sample music;

  std::vector<MapPin*> pins;
};

#endif  // MAP_H
