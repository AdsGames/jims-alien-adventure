#include "./Map.h"

#include "../globals.h"

void Map::init() {
  // Load music
  music = asw::assets::loadMusic("assets/music/the-experiment.ogg");

  // Load images
  map_image = asw::assets::loadTexture("assets/images/map/map.png");

  // Add pins
  for (int i = 0; i < LevelData::GetLevelData()->GetNumLevels(); i++) {
    Level* l = LevelData::GetLevelData()->GetLevel(i);
    pins.push_back(
        new MapPin(l->pin_x, l->pin_y, l->folder, l->completed, l->id));
  }

  // Start music
  asw::sound::playMusic(music, 255);
}

void Map::update(float deltaTime) {
  Scene::update(deltaTime);

  // Pin logic
  auto is_hovering = false;
  for (auto p : pins) {
    if (p->hover()) {
      is_hovering = true;

      if (asw::input::wasButtonPressed(asw::input::MouseButton::LEFT)) {
        levelOn = p->getId();
        sceneManager.setNextScene(States::Game);
      }
    }
  }

  // Set cursor
  if (!is_hovering) {
    asw::input::setCursor(asw::input::CursorId::CROSSHAIR);
  } else {
    asw::input::setCursor(asw::input::CursorId::POINTER);
  }

  // Back to menu
  if (asw::input::wasKeyPressed(asw::input::Key::ESCAPE)) {
    sceneManager.setNextScene(States::Menu);
  }
}

void Map::draw() {
  // Draw background to screen
  asw::draw::clearColor(asw::util::makeColor(255, 255, 255));

  // Map image
  asw::draw::sprite(map_image, asw::Vec2<float>(0, 0));

  // Locations
  for (auto p : pins) {
    p->draw();
  }
}
