#include "globals.h"

// Our stuff
bool distance_is_reached = false;
bool switch_flicked = false;

float distance_travelled;
int level_distance = 100;
bool joystick_enabled = false;

// Frames
int frames_done;

//State variables
int stateID;
int nextState;
string levelOn = "cn_tower";
