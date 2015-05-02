#ifndef GLOBALS_H
#define GLOBALS_H

//All libaries
#include <allegro.h>

// Set next state
void set_next_state( int newState );

//Game states
enum GameStates
{
    STATE_NULL,
    STATE_INIT,
    STATE_INTRO,
    STATE_MENU,
    STATE_EDIT,
    STATE_GAME,
    STATE_EXIT,
};

// Endgame Variables
extern bool is_game_done;
extern bool input_mode;
extern bool switch_flicked;
// Frames
extern int frames_done;
extern float distance_travelled;

// Resdiv
extern int resDiv;
extern bool single_player;

//State variables
extern int stateID;
extern int nextState;
extern int levelOn;

#endif
