#include "Stair.h"

#include "LevelData.h"
#include "tools.h"
#include "globals.h"

BITMAP *Stair::images[4] = { nullptr };
int Stair::stair_count = 0;
bool Stair::last_stair_placed = false;

// Constructor
Stair::Stair (float x) {
  this -> x = x;

  y = location_y (x);
  type = 0;
  transparency_bitmap = create_bitmap (SCREEN_W, SCREEN_H);
  rectfill (transparency_bitmap, 0, 0, SCREEN_W, SCREEN_H, makecol (255, 0, 255));

  if (stair_count == 0)
    load_sprites();
  stair_count++;
}

// Copy constructor
Stair::Stair (const Stair& s) {
  x = s.x;
  y = s.y;
  type = s.type;

  transparency_bitmap = create_bitmap (SCREEN_W, SCREEN_H);

  clear_to_color(transparency_bitmap, 0xFF00FF);

  if (stair_count == 0)
    load_sprites();
  stair_count++;
}

// Destructor
Stair::~Stair() {
  stair_count--;
  if (stair_count == 0)
    unload_sprites();

  destroy_bitmap(transparency_bitmap);
}

// Load images
void Stair::load_sprites() {
  std::string folder = LevelData::GetLevelData() -> GetLevel(levelOn) -> folder;
  images[IMG_STAIRS] = load_png_ex (("images/levels/" + folder + "/stairs.png").c_str());
  images[IMG_TOP_RED] = load_png_ex (("images/levels/" + folder + "/stage_end_red.png").c_str());
  images[IMG_TOP_GREEN] = load_png_ex (("images/levels/" + folder + "/stage_end_green.png").c_str());
  images[IMG_BRICK] = load_png_ex (("images/levels/" + folder + "/brick.png").c_str());
}

// Unload images
void Stair::unload_sprites() {
  destroy_bitmap(images[0]);
  destroy_bitmap(images[1]);
  destroy_bitmap(images[2]);
  destroy_bitmap(images[3]);
}

// Update those stairs
void Stair::update (float distanceRemaining, float speed) {
  // Move
  x -= speed;

  // Go back to start
  if (y > SCREEN_H && !last_stair_placed) {
    if (distanceRemaining < SCREEN_W - 100) {
      type = 1;
      last_stair_placed = true;
    }
    x += images[IMG_STAIRS] -> w * int(SCREEN_W / images[IMG_STAIRS] -> w);
  }

  // Turn green
  if (distanceRemaining == 0 && type == 1) {
    type = 2;
  }

  // Top of map
  y = type == 0 ? location_y (x - 30) : location_y (x);
}


// Line y position
float Stair::location_y (float last_x) {
  return SCREEN_H - ((last_x - SCREEN_W / 4) / 30) * 37;
}

// Draw those stairs
// YES WE CAN
void Stair::draw (BITMAP *buffer) {
  // Draw stair and rectangle beside for effect
  for (int i = x + images[IMG_STAIRS] -> w - 30; i < SCREEN_W; i += images[IMG_BRICK] -> w) {
    draw_sprite (buffer, images[IMG_BRICK], i, y + images[IMG_STAIRS] -> h);
  }

  draw_sprite (buffer, images[type], x, y);

  if (type == 1 || type == 2) {
    blit (transparency_bitmap, buffer, 0, 0, x + images[type] -> w, y, SCREEN_W, SCREEN_H);
    line (buffer, x + images[type] -> w - 1, y + 30, x + images[type] -> w - 1, SCREEN_H, makecol (168, 148, 148));
  }
}
