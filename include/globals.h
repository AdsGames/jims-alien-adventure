#ifndef GLOBALS_H
#define GLOBALS_H

//All libaries
#include <allegro.h>
#include <string>

// Endgame Variables
extern bool distance_is_reached;
extern bool switch_flicked;

extern bool beaten_levels[10];

extern int level_distance;
extern float distance_travelled;
extern bool joystick_enabled;

// Frames
extern int frames_done;

extern std::string levelOn;

#endif
