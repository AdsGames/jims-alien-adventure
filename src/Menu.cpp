#include "Menu.h"

#include "globals.h"
#include "tools.h"

Menu::Menu() {
  // Load music
  music = load_ogg_ex("music/JAA-Theme.ogg");

  // Load sound
  NOTALLOWED = load_sample_ex("sounds/goat.wav");

  // Load images
  background[0] = load_png_ex("images/menu/menu.png");
  background[1] = load_png_ex ("images/menu/menu_2.png");

  title = load_png_ex ("images/menu/title.png");
  sky = load_png_ex ("images/levels/statue_of_liberty/sky.png");
  city = load_png_ex ("images/levels/statue_of_liberty/parallax.png");
  cursor = load_png_ex ("images/menu/cursor1.png");
  cursor2 = load_png_ex ("images/menu/cursor2.png");

  little_xbox_buttons = load_png_ex ("images/menu/angle_buttons.png");

  //Sets Font
  font = load_font_ex("fonts/dosis.pcx");

  // Allow transparency
  set_alpha_blender();

  // Variable set
  title_y = -(title -> h + 20);
  city_x = 0;
  switchFlipped = false;

  // Buttons
  start = Button (30, 190);
  start.SetImages("images/menu/button_play.png", "images/menu/button_pushed_play.png");

  story = Button (195, 190);
  story.SetImages("images/menu/button_story.png", "images/menu/button_pushed_story.png");

  options = Button (30, 300);
  options.SetImages("images/menu/button_options.png", "images/menu/button_pushed_options.png");

  exit = Button (195, 300);
  exit.SetImages("images/menu/button_exit.png", "images/menu/button_pushed_exit.png");

  play_sample (music, 255, 128, 1000, 1);
}

Menu::~Menu() {
  // Destory Bitmaps
  destroy_bitmap (title);
  destroy_bitmap (sky);
  destroy_bitmap (city);
  destroy_bitmap (cursor);
  destroy_bitmap (background[0]);
  destroy_bitmap (background[1]);

  // Clear away goats
  goats.clear();

  // Stop music
  stop_sample (music);

  // Clear keybuff
  clear_keybuf();

  // Fade out
  highcolor_fade_out (32);
}

void Menu::update(StateEngine *engine) {
  // Poll joystick
  poll_joystick();

  // Drop title
  title_y = title_y < 20 ? title_y + (20 - title_y) / 80 : 100;

  // Move city
  city_x = city_x < -city -> w ? city_x + city -> w : city_x - 2;

  // Buttons
  if (start.Clicked())
    setNextState (engine, StateEngine::STATE_MAP);

  if (story.Clicked())
    setNextState (engine, StateEngine::STATE_STORY);

  if (options.Clicked()) {
    play_sample (NOTALLOWED, 255, 125, 1000, 0);
    float randomDistance = float (random (2, 6)) / 10.0f;
    goat newGoat (SCREEN_W, random (0, SCREEN_H), randomDistance, randomDistance * 3);
    goats.push_back (newGoat);
  }

  if (exit.Clicked())
    setNextState (engine, StateEngine::STATE_EXIT);

  // Motherfing goats!
  if (random (0, 80) == 0) {
    float randomDistance = float (random (2, 6)) / 10;
    goat newGoat (SCREEN_W, random (0, SCREEN_H), randomDistance, randomDistance * 3);
    goats.push_back (newGoat);
  }

  // Update goats
  for (auto g = goats.begin(); g < goats.end(); ) {
    g -> update();
    g -> fall (switchFlipped * 5);
    g -> offScreen() ? g = goats.erase(g) : ++g;
  }

  // Flip switch
  if (mouse_b & 1) {
    if ((!switchFlipped && collision (595, 607, mouse_x, mouse_x, 236, 248, mouse_y, mouse_y)) ||
         (switchFlipped && collision (579, 591, mouse_x, mouse_x, 235, 247, mouse_y, mouse_y))) {
      switchFlipped = !switchFlipped;
    }
  }
}

void Menu::draw(BITMAP *buffer) {
  // Draw background to screen
  rectfill (buffer, 0, 0, SCREEN_W, SCREEN_H, makecol (255, 255, 255));

  // Sky
  stretch_sprite (buffer, sky, 0, 0, SCREEN_W, SCREEN_H);

  // City scroll
  draw_sprite (buffer, city, city_x, SCREEN_H - city -> h);
  draw_sprite (buffer, city, city_x + city -> w, SCREEN_H - city -> h);

  // Draw goats
  for (unsigned int i = 0; i < goats.size(); i++) {
    goats.at (i).draw (buffer);
  }

  // Stairs
  draw_sprite (buffer, background[switchFlipped], 0, 0);

  // Title
  draw_trans_sprite (buffer, title, 20, title_y);

  // Buttons
  start.Draw (buffer);
  story.Draw (buffer);
  options.Draw (buffer);
  exit.Draw (buffer);

  // Joystick helpers
  if (joystick_enabled) {
    masked_blit (little_xbox_buttons, buffer, 60, 0, start.GetX()   + 21 - 4 * start.Hover()  , start.GetY()   + 114 - start.Hover()  , 20, 20);
    masked_blit (little_xbox_buttons, buffer, 40, 0, story.GetX()   + 25 - 4 * story.Hover()  , story.GetY()   + 114 - story.Hover()  , 20, 20);
    masked_blit (little_xbox_buttons, buffer,  0, 0, options.GetX() + 25 - 4 * options.Hover(), options.GetY() + 114 - options.Hover(), 20, 20);
    masked_blit (little_xbox_buttons, buffer, 20, 0, exit.GetX()    + 25 - 4 * exit.Hover()   , exit.GetY()    + 114 - exit.Hover()   , 20, 20);
  }

  // Cursor
  if (start.Hover() || story.Hover() || options.Hover() || exit.Hover()) {
    draw_sprite (buffer, cursor2, mouse_x, mouse_y);
  }
  else {
    draw_sprite (buffer, cursor, mouse_x, mouse_y);
  }
}
