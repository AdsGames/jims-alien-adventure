#pragma once

#include <asw/asw.h>

#include "./States.h"

// Intro screen of game
class Intro : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float dt) override;

  void draw() override;

 private:
  // Images
  asw::Texture splash;
  asw::Texture logo;

  // Time
  float timer;
};
