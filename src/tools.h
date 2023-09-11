#ifndef TOOLS_H
#define TOOLS_H

#include <asw/asw.h>

// Collision
extern bool collision(int xMin1,
                      int xMax1,
                      int xMin2,
                      int xMax2,
                      int yMin1,
                      int yMax1,
                      int yMin2,
                      int yMax2);

// Random number generator
extern int random(int low, int high);

#endif  // TOOLS_H
