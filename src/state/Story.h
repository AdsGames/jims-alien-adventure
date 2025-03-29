#pragma once

#include <asw/asw.h>

#include "./States.h"

class Story : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

 private:
  // Frequncy in milliseconds
  const float flash_frequency = 500.0F;
  float flasher{0};

  asw::Texture story_splash;
  asw::Font font;

  asw::Vec2<float> text_position;
};
