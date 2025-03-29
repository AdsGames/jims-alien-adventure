#include "LevelData.h"

#include <asw/asw.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "tools.h"

LevelData* LevelData::instance = nullptr;

LevelData::LevelData(const std::string& path) {
  if (!Load(path)) {
    asw::util::abortOnError("Could not open config file " + path);
  }
}

bool LevelData::Load(const std::string& path) {
  // Open file or abort if it does not exist
  std::ifstream file(path);
  if (!file.is_open()) {
    return false;
  }

  // Create buffer
  nlohmann::json doc = nlohmann::json::parse(file);

  // Get levels
  int id = 0;
  for (auto const& level : doc) {
    Level* l = new Level;

    l->distance = level["distance"];
    l->time = level["time"];
    l->pin_x = level["pinx"];
    l->pin_y = level["piny"];
    l->folder = level["folder"];
    l->name = level["name"];
    l->id = id;
    l->completed = false;
    levels.push_back(l);

    id++;
  }

  return true;
}

int LevelData::GetNumLevels() {
  return levels.size();
}

Level* LevelData::GetLevel(unsigned int id) {
  return (id > levels.size()) ? nullptr : levels.at(id);
}

LevelData* LevelData::GetLevelData() {
  if (!instance) {
    instance = new LevelData("./assets/levels.json");
  }

  return instance;
}
