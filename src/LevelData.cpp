#include "LevelData.h"

#include <asw/asw.h>
#include <fstream>
#include <nlohmann/json.hpp>

LevelData::LevelData(const std::string& file) {
  Load(file);
}

void LevelData::Load(const std::string& path) {
  // Open file or abort if it does not exist
  std::ifstream file(path);
  if (!file.is_open()) {
    asw::util::abort_on_error("Could not open config file " + path);
  }

  // Create buffer
  const nlohmann::json doc = nlohmann::json::parse(file);

  // Get levels
  int id = 0;
  for (auto const& level : doc) {
    auto l = Level();
    l.distance = level["distance"];
    l.time = level["time"];
    l.pin_x = level["pinx"];
    l.pin_y = level["piny"];
    l.folder = level["folder"];
    l.name = level["name"];
    l.id = id;
    l.completed = false;

    levels.push_back(l);

    id++;
  }
}

void LevelData::Save(const std::string& path) {
  nlohmann::json doc;

  for (const auto& l : levels) {
    doc.push_back({{"distance", l.distance},
                   {"time", l.time},
                   {"pinx", l.pin_x},
                   {"piny", l.pin_y},
                   {"folder", l.folder},
                   {"name", l.name},
                   {"completed", l.completed}});
  }

  std::ofstream file(path);
  if (!file.is_open()) {
    asw::util::abort_on_error("Could not open config file " + path);
  }

  file << doc.dump(2);
}

int LevelData::GetNumLevels() {
  return levels.size();
}

std::optional<Level> LevelData::GetLevel(unsigned int id) {
  if (id >= levels.size()) {
    return std::nullopt;
  }

  return std::optional<Level>(levels.at(id));
}
