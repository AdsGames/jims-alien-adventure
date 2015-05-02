#include "globals.h"

BITMAP* tileSprites[400][8];
BITMAP* projectileSprites[10][3];

// Frames
int frames_done;
bool single_player = false;
bool input_mode = false;

bool is_game_done = false;
bool switch_flicked = false;
float distance_travelled;

int level_distance = 92;


// Resdiv
int resDiv;

//State variables
int stateID;
int nextState;
int levelOn;
