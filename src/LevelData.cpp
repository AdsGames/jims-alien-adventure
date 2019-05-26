#include "LevelData.h"

#include <allegro.h>
#include <iostream>

LevelData *LevelData::instance = nullptr;

LevelData::LevelData(const char *file) {
  Load(file);
}

LevelData::~LevelData() {

}

bool LevelData::Load(const char *file) {
  push_config_state();
  set_config_file(file);

  // Get levels
  int num_levels = get_config_int("levels", "numlevels", -1);

  // Invalid file
  if (num_levels == -1)
    return false;

  // Iterate over levels
  for (int i = 0; i < num_levels; i++) {
    Level *l = new Level;
    const char *level_header = (std::string("level") + std::to_string(i)).c_str();
    l -> distance = get_config_int(level_header, "distance", -1);
    l -> time = get_config_int(level_header, "time", -1);
    l -> pin_x = get_config_int(level_header, "pinx", -1);
    l -> pin_y = get_config_int(level_header, "piny", -1);
    l -> folder = std::string(get_config_string(level_header, "folder", ""));
    l -> name = std::string(get_config_string(level_header, "name", ""));
    l -> id = i;
    l -> completed = false;
    levels.push_back(l);
  }

  pop_config_state();

  return true;
}

int LevelData::GetNumLevels() {
  return levels.size();
}

Level *LevelData::GetLevel(unsigned int id) {
  return (id > levels.size()) ? nullptr : levels.at(id);
}

LevelData *LevelData::GetLevelData() {
  if (!instance)
    instance = new LevelData("levels.ini");

  return instance;
}
