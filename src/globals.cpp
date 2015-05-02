#include "globals.h"

BITMAP* tileSprites[400][8];
BITMAP* projectileSprites[10][3];

// Frames
int frames_done;
bool single_player = false;
<<<<<<< HEAD
bool is_game_done;
bool input_mode = true;
=======
bool is_game_done = false;

>>>>>>> 4d7dbfb873b339bf811dae82cc0aa728d37cca82

// Resdiv
int resDiv;

//State variables
int stateID;
int nextState;
int levelOn;
