#pragma once

#include <asw/asw.h>
#include <asw/util/Timer.h>

#include "./States.h"

// Intro screen of game
class Intro : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  // Images
  asw::Texture splash;
  asw::Texture logo;

  // Time
  Timer timer;
};
