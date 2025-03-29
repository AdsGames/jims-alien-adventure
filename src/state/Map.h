#pragma once

#include <asw/asw.h>
#include <vector>

#include "../LevelData.h"
#include "../MapPin.h"
#include "./States.h"

class Map : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  // Map/GUI
  asw::Texture map_image;
  asw::Texture cursor;

  asw::Music music;

  std::vector<MapPin*> pins;
};
