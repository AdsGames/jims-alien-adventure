#include "Goat.h"

#include "tools.h"

BITMAP *Goat::goat_image[2] = { nullptr };
int Goat::goat_count = 0;

Goat::Goat (float x, float y, float scale, float speed) {
  this -> x = x;
  this -> y = y;
  this -> scale = scale;
  this -> speed = speed;

  if (goat_count == 0)
    load_sprites();
  goat_count++;
}

Goat::Goat (const Goat& g) {
  this -> x = g.x;
  this -> y = g.y;
  this -> scale = g.scale;
  this -> speed = g.speed;

  if (goat_count == 0)
    load_sprites();
  goat_count++;
}

Goat::~Goat() {
  goat_count--;
  if (goat_count == 0)
    unload_sprites();
}

// Load images
void Goat::load_sprites() {
  goat_image[0] = load_png_ex("images/goat_alien.png");
  goat_image[1] = load_png_ex("images/goat_alien_2.png");
}

// Unload images
void Goat::unload_sprites() {
  destroy_bitmap(goat_image[0]);
  destroy_bitmap(goat_image[1]);
}

// Update
void Goat::update() {
  x -= speed;
}

// Kill
bool Goat::offScreen() {
  return (x + goat_image[0] -> w - speed < 0 || x - speed > SCREEN_W || y > SCREEN_H || y + goat_image[0] -> h < 0);
}

// Fall!
void Goat::fall (float speed) {
  y += speed;
}

// Draw
void Goat::draw (BITMAP *buffer) {
  stretch_sprite (buffer, goat_image[random (0, 1)], x, y, goat_image[0] -> w * scale, goat_image[1] -> h * scale);
}
