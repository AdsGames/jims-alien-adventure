#pragma once

#include <asw/asw.h>

#include "./States.h"

class Init : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;
};
