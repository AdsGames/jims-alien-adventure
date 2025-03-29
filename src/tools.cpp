#include "tools.h"

#include <fstream>

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
