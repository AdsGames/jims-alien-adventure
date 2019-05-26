#include "tools.h"

#include <logg.h>
#include <loadpng.h>
#include <sstream>
#include <fstream>

//Iterates through the number of buttons in a joystick and returns true if any keys are pressed
bool keyboard_keypressed() {
  bool keypressed = false;

  for (int i = 0; i < 125; i++) {
    if (key[i]) {
      keypressed = true;
    }
  }

  return keypressed;

}

//Iterates through the number of buttons in a joystick and returns true if any buttons are pressed
bool joy_buttonpressed() {
  bool buttonpressed = false;

  for (int i = 0; i < joy[0].num_buttons; i++) {
    if (joy[0].button[i].b) {
      buttonpressed = true;
    }
  }

  return buttonpressed;
}

//Collision
bool collision (int xMin1, int xMax1, int xMin2, int xMax2, int yMin1, int yMax1, int yMin2, int yMax2) {
  return (xMin1 < xMax2 && yMin1 < yMax2 && xMin2 < xMax1 && yMin2 < yMax1);
}

//Checks if file exists
bool fexists (const char *filename) {
  std::ifstream ifile (filename);
  return !ifile.fail();
}

//Random number generator. Use int random(lowest,highest);
int random (int newLowest, int newHighest) {
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest + int (range * rand() / (RAND_MAX + 1.0));
  return randomNumber;
}

// Fade in
void highcolor_fade_in (BITMAP *bmp_orig, int speed) {
  BITMAP *bmp_buff = create_bitmap (SCREEN_W, SCREEN_H);
  BITMAP *str_orig = create_bitmap (SCREEN_W, SCREEN_H);
  stretch_sprite (str_orig, bmp_orig, 0, 0, SCREEN_W, SCREEN_H);

  if (speed <= 0) {
    speed = 16;
  }

  for (int a = 0; a < 256; a += speed) {
    clear (bmp_buff);
    set_trans_blender (0, 0, 0, a);
    draw_trans_sprite (bmp_buff, str_orig, 0, 0);
    vsync();
    stretch_sprite (screen, bmp_buff, 0, 0,  SCREEN_W, SCREEN_H);
  }

  stretch_sprite (screen, str_orig, 0, 0,  SCREEN_W, SCREEN_H);
}

// Fade out
void highcolor_fade_out (int speed) {
  BITMAP *bmp_buff = create_bitmap (SCREEN_W, SCREEN_H);
  BITMAP *bmp_orig = create_bitmap (SCREEN_W, SCREEN_H);
  blit (screen, bmp_orig, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

  if (speed <= 0) {
    speed = 16;
  }

  for (int a = 255 - speed; a > 0; a -= speed) {
    clear (bmp_buff);
    set_trans_blender (0, 0, 0, a);
    draw_trans_sprite (bmp_buff, bmp_orig, 0, 0);
    vsync();
    stretch_sprite (screen, bmp_buff, 0, 0,  SCREEN_W, SCREEN_H);
  }

  destroy_bitmap (bmp_orig);
  rectfill (screen, 0, 0,  SCREEN_W, SCREEN_H, makecol (0, 0, 0));
}

/*
 *  ERROR REPORTING
 */
void abort_on_error (const char *message) {
  if (screen != NULL) {
    set_gfx_mode (GFX_TEXT, 0, 0, 0, 0);
  }

  allegro_message ("%s.\n %s\n", message, allegro_error);
  exit (-1);
}

// Load image
BITMAP* load_png_ex(const char *path) {
  BITMAP *temp = nullptr;
  if (!(temp = load_png(path, nullptr))) {
    abort_on_error ((std::string("Cannot find image (") + path + ") \n Please check your files and try again").c_str());
  }
  return temp;
}

// Load ogg
SAMPLE* load_ogg_ex(const char *path) {
  SAMPLE *temp = nullptr;
  if (!(temp = logg_load(path))) {
    abort_on_error ((std::string("Cannot find music (") + path + ") \n Please check your files and try again").c_str());
  }
  return temp;
}


// Load sample
SAMPLE* load_sample_ex(const char *path) {
  SAMPLE *temp = nullptr;
  if (!(temp = load_sample(path))) {
    abort_on_error ((std::string("Cannot find sample (") + path + ") \n Please check your files and try again").c_str());
  }
  return temp;
}

// Load font
FONT* load_font_ex(const char *path) {
  FONT *temp = nullptr;
  if (!(temp = load_font(path, nullptr, nullptr))) {
    abort_on_error ((std::string("Cannot find font (") + path + ") \n Please check your files and try again").c_str());
  }
  return temp;
}


