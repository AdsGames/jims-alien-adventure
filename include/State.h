/**
 * State for machine and State Engine
 * Allan Legemaate
 * 30/12/2016
 * Compartmentalize program into states
 *   which can handle only their own logic,
 *   drawing and transitions
 */

#ifndef STATE_H
#define STATE_H

#include <allegro.h>

// Class
class State;

/*****************
 * STATE ENGINE
 *****************/
class StateEngine {
  public:
    // Init
    StateEngine();

    // Update
    void update();

    // Draw
    void draw(BITMAP *buffer);

    // Set next state
    void setNextState(int newState);

    // Get state id
    int getStateId();

    // Game states
    enum programStates {
      STATE_NULL,
      STATE_EXIT,
      STATE_INIT,
      STATE_INTRO,
      STATE_MENU,
      STATE_STORY,
      STATE_GAME,
      STATE_MAP
    };

  private:
    // Change state
    void changeState();

    // Stores states
    State *state;

    // Next state
    int nextState = STATE_NULL;

    // State id
    int currentState = STATE_NULL;

};

/*********
 * STATE
 *********/
class State {
  public:
    State() {}

    // Virtual destructor
    virtual ~State() {};

    // Draw to screen
    virtual void draw(BITMAP *buffer) = 0;

    // Update logic
    virtual void update(StateEngine *engine) = 0;

    // Change state
    void setNextState(StateEngine *engine, int state);

    // Get status
    int getStatus();

  private:
    // Disallow copy
    State(const State &);
    State &operator=(const State &);
};

#endif // STATE_H
