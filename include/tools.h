#ifndef TOOLS_H
#define TOOLS_H

#include <allegro.h>

// Key or joy button pressed
extern bool key_down();
extern bool button_down();

//Collision
extern bool collision (int xMin1, int xMax1, int xMin2, int xMax2, int yMin1, int yMax1, int yMin2, int yMax2);

// Mouse position including resolution difference
extern int mouseX();
extern int mouseY();

//Random number generator
extern int random (int low, int high);

// Fade in and out
extern void highcolor_fade_in (BITMAP *bmp_orig, int speed);
extern void highcolor_fade_out (int speed);

// Error reporting
extern void abort_on_error (const char *message);

// Load image
extern BITMAP* load_png_ex(const char *path);

// Load ogg
extern SAMPLE* load_ogg_ex(const char *path);

// Load sample
extern SAMPLE* load_sample_ex(const char *path);

// Load font
extern FONT* load_font_ex(const char *path);


#endif // TOOLS_H
