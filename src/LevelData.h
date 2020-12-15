#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>
#include <string>

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
    bool Load(const char *file);
    Level *GetLevel(unsigned int id);

    int GetNumLevels();

    static LevelData *GetLevelData();
  private:
    explicit LevelData(const char *file);

    static LevelData *instance;
    std::vector<Level *> levels;
};

#endif // LEVELDATA_H
