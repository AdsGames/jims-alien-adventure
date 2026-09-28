#pragma once

#include <asw/asw.h>
#include <memory>

#include "../LevelData.h"
#include "./States.h"

class Map : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float dt) override;

  void draw() override;

 private:
  // Map/GUI
  asw::Texture map_image;

  asw::Music music;

  // Level pins
  std::unique_ptr<asw::ui::Root> ui;
};
