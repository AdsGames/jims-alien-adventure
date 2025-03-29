#ifndef LEVELDATA_H
#define LEVELDATA_H

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
  bool Load(const std::string& file);
  Level* GetLevel(unsigned int id);

  int GetNumLevels();

  static LevelData* GetLevelData();

 private:
  explicit LevelData(const std::string& file);

  static LevelData* instance;
  std::vector<Level*> levels;
};

#endif  // LEVELDATA_H
