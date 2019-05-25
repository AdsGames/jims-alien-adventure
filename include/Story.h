#ifndef STORY_H
#define STORY_H

#include "GameState.h"

#include <allegro.h>
#include <loadpng.h>
#include "tools.h"
#include "globals.h"

class Story : public GameState {
  private:
    // Map/GUI
    bool is_showing_text;
    BITMAP *buffer;
    BITMAP *story_splash;
  protected:
  public:
    //Main loop functions
    Story();
    void update();
    void draw();
    ~Story();
};

#endif // STORY_H
