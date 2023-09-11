#include "tools.h"

#include <fstream>
#include <random>

// Random device
std::mt19937 rng(time(nullptr));

// Collision
bool collision(int xMin1,
               int xMax1,
               int xMin2,
               int xMax2,
               int yMin1,
               int yMax1,
               int yMin2,
               int yMax2) {
  return (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1);
}

// Random number generator. Use int random(lowest,highest);
int random(int low, int high) {
  std::uniform_int_distribution<std::mt19937::result_type> dist6(
      low, high);  // distribution in range [1, 6]
  return dist6(rng);
}