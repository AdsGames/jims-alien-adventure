#include "Game.h"

volatile int Game::timer1 = 00;

Game::Game()
{
  // Init
  init();
}

void Game::gameTicker(){
  timer1++;
}
END_OF_FUNCTION(gameTicker)

struct stair{
  float x;
  float y;
  BITMAP* image;
};

// All stairs
vector<stair> allStairs;

void Game::init(){
  // Init fmod
  FSOUND_Init (44100, 32, 0);

  // Init variables
  scroll_speed = 1.0;

  // Creates a random number generator (based on time)
  srand (time(NULL));

  // Load images
  if(!(image_stairs = load_bitmap( "images/stairs.png", NULL))){
    abort_on_error( "Cannot find image images/stairs.png \n Please check your files and try again");
  }

  // Other Sprites
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Temporary fonts
  FONT *f1, *f2, *f3, *f4, *f5;

  //Sets Font
  if(!(f1 = load_font(("fonts/arial_black.pcx"), NULL, NULL))){
    abort_on_error( "Cannot find font fonts/arial_black.png \n Please check your files and try again");
  }

  f2 = extract_font_range(f1, ' ', 'A'-1);
  f3 = extract_font_range(f1, 'A', 'Z');
  f4 = extract_font_range(f1, 'Z'+1, 'z');

  //Merge fonts
  font = merge_fonts(f4, f5 = merge_fonts(f2, f3));

  //Destroy temporary fonts
  destroy_font(f1);
  destroy_font(f2);
  destroy_font(f3);
  destroy_font(f4);
  destroy_font(f5);

  // Stairs (offset is 30 px)
  for( int i = 0; i < SCREEN_W; i += 30 ){
    stair newStair;
    newStair.x = i;
    newStair.y = location_y(i);
    newStair.image = image_stairs;
    allStairs.push_back(newStair);
  }
}

// Update game state
void Game::update(){
  // Stairs!
  for( int i = 0; i < allStairs.size(); i ++ ){
    // Move
    allStairs.at(i).x += scroll_speed;
    allStairs.at(i).y = location_y(allStairs.at(i).x);

    // reset stairs
    if( allStairs.at(i).y < -(allStairs.at(i).image -> h)){
      allStairs.at(i).x = allStairs.at(find_bottom_stair(i)).x - (allStairs.at(i).image -> w)*2;
      allStairs.at(i).y = location_y(allStairs.at(i).x);
    }
  }
}

// Draw game state
void Game::draw(){
  // Background
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255, 255, 255));

  // Stairs!
  for( int i = 0; i < allStairs.size(); i ++ ){
    // Draw
    rectfill( buffer, allStairs.at(i).x + 30, allStairs.at(i).y, SCREEN_W, allStairs.at(i).y + allStairs.at(i).image -> h - 1, makecol( 115, 40, 0));
    draw_sprite( buffer, allStairs.at(i).image, allStairs.at(i).x, allStairs.at(i).y);
  }

  // Buffer
  draw_sprite( screen, buffer, 0, 0);
}

// Line y position
float Game::location_y( float oldX){
  return SCREEN_H - (oldX/30) * 37;
}

// Line y position
int Game::find_bottom_stair( int stairIndex){
  // New index
  int bottomIndex = stairIndex + 1;

  // Too High? Wrap around (only happens when number is max)
  if( bottomIndex >= allStairs.size()){
    bottomIndex = 0;
  }

  return bottomIndex;
}

Game::~Game()
{
  // Destroy images
  destroy_bitmap( buffer);

  // Fade out
  highcolor_fade_out(16);

  // Clean up fmod
  FSOUND_Close();
}
