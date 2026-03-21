#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <optional>
#include <string>
#include <vector>

struct Level {
  int id;
  std::string folder;
  std::string name;
  bool completed;
  int distance;
  float time;
  int pin_x;
  int pin_y;
};

class LevelData {
 public:
  LevelData() = default;
  explicit LevelData(const std::string& file);

  void Load(const std::string& file);
  void Save(const std::string& file);
  std::optional<Level> GetLevel(unsigned int id);

  int GetNumLevels();

 private:
  std::vector<Level> levels;
};

#endif  // LEVELDATA_H
