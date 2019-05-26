#include "stair.h"
#include "globals.h"

#include "tools.h"
#include "globals.h"

int stair::numberStairs = 0;
const int stair::maxScrollSpeed = 6;
float stair::scrollSpeed = 0;
float stair::locationOfFinal = 0;

int stair::stair_count = 0;
BITMAP *stair::images[4] = { nullptr };
bool stair::final_stair_placed = false;

// Constructor
stair::stair (float x, float y, int type) {
  this -> x = x;
  this -> y = y;
  this -> type = type;

  stairID = numberStairs;
  numberStairs++;

  transparency_bitmap = create_bitmap (SCREEN_W, SCREEN_H);
  rectfill (transparency_bitmap, 0, 0, SCREEN_W, SCREEN_H, makecol (255, 0, 255));

  if (stair_count == 0)
    load_sprites();
  stair_count++;
}

// Copy constructor
stair::stair (const stair& s) {
  x = s.x;
  y = s.y;
  type = s.type;
  stairID = s.stairID;

  transparency_bitmap = create_bitmap (SCREEN_W, SCREEN_H);
  rectfill (transparency_bitmap, 0, 0, SCREEN_W, SCREEN_H, makecol (255, 0, 255));

  if (stair_count == 0)
    load_sprites();
  stair_count++;
}

// Destructor
stair::~stair() {
  stair_count--;
  if (stair_count == 0)
    unload_sprites();

  destroy_bitmap(transparency_bitmap);
}

// Load images
void stair::load_sprites() {
  images[IMG_STAIRS] = load_png_ex (("images/stairs/" + levelOn + "/stairs.png").c_str());
  images[IMG_BRICK] = load_png_ex (("images/stairs/" + levelOn + "/brick.png").c_str());
  images[IMG_TOP_RED] = load_png_ex (("images/stairs/" + levelOn + "/stage_end_red.png").c_str());
  images[IMG_TOP_GREEN] = load_png_ex (("images/stairs/" + levelOn + "/stage_end_green.png").c_str());
}

// Unload images
void stair::unload_sprites() {
  destroy_bitmap(images[0]);
  destroy_bitmap(images[1]);
  destroy_bitmap(images[2]);
  destroy_bitmap(images[3]);
}


int stair::getType() {
  return type;
}

void stair::setType (int type) {
  this -> type = type;
}

// Update those stairs
void stair::update (std::vector<stair> *allStairsCopy) {
  // Reset stairs
  if (y > SCREEN_H + images[IMG_STAIRS] -> h) {
    if (!distance_is_reached) {
      x = allStairsCopy -> at (find_top_stair (stairID)).x + 30;
      y = location_y (x);
    }
    else if (distance_is_reached && !final_stair_placed) {
      type = 1;
      final_stair_placed = true;
      x = allStairsCopy -> at (find_top_stair (stairID)).x + 30;
      y = location_y (x) - 30;
    }
  }
}

void stair::movement() {
  // Move
  x -= scrollSpeed;

  // Top of map
  if (type == 1 || type == 2) {
    y = location_y (x);
    locationOfFinal = y + 60;
  }
  else {
    y = location_y (x - 30);
  }
}

// Line y position
float stair::location_y (float last_x) {
  return SCREEN_H - ((last_x - SCREEN_W / 4) / 30) * 37;
}

// Find the top
int stair::find_top_stair (int index) {
  return (index - 1) < 0 ? numberStairs - 1 : index - 1;
}

// Draw those stairs
// YES WE CAN
void stair::draw (BITMAP *buffer) {
  // Draw stair and rectangle beside for effect
  for (int i = x + images[IMG_STAIRS] -> w - 30; i < SCREEN_W; i += images[IMG_BRICK] -> w) {
    draw_sprite (buffer, images[IMG_BRICK], i, y + images[IMG_STAIRS] -> h);
  }

  // Swaggin images
  switch (type) {
    case 0:
      draw_sprite (buffer, images[IMG_STAIRS], x, y);
      break;
    case 1:
      draw_sprite (buffer, images[IMG_TOP_RED], x, y);
      blit (transparency_bitmap, buffer, 0, 0, x + images[IMG_TOP_RED] -> w, y, SCREEN_W, SCREEN_H);
      line (buffer, x + images[IMG_TOP_RED] -> w - 1, y + 30, x + images[IMG_TOP_RED] -> w - 1, SCREEN_H, makecol (168, 148, 148));
      break;
    case 2:
      draw_sprite (buffer, images[IMG_TOP_GREEN], x, y);
      blit (transparency_bitmap, buffer, 0, 0, x + images[IMG_TOP_GREEN] -> w, y, SCREEN_W, SCREEN_H);
      line (buffer, x + images[IMG_TOP_GREEN]-> w - 1, y + 30, x + images[IMG_TOP_GREEN] -> w - 1, SCREEN_H, makecol (168, 148, 148));
      break;
    default:
      break;
  }
}
