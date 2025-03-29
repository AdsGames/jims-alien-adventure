#include "./Map.h"

#include "../globals.h"
#include "../tools.h"

void Map::init() {
  // Load music
  music = asw::assets::loadMusic("assets/music/the-experiment.ogg");

  // Load images
  map_image = asw::assets::loadTexture("assets/images/map/map.png");
  cursor = asw::assets::loadTexture("assets/images/map/cursor.png");

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

  // Change level
  if (asw::input::mouse.pressed[1]) {
    for (auto p : pins) {
      if (p->hover()) {
        levelOn = p->GetID();
        sceneManager.setNextScene(States::Game);
      }
    }
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
    p->Draw();
  }

  // Cursor
  auto cursorSize = asw::util::getTextureSize(cursor);
  asw::draw::sprite(cursor,
                    asw::Vec2<float>(asw::input::mouse.x - cursorSize.x / 2,
                                     asw::input::mouse.y - cursorSize.y / 2));
}
