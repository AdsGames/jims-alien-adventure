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

// All stairs
vector<stair> allStairs;

void Game::init(){
  // Init fmod
  FSOUND_Init (44100, 32, 0);

  // Init variables
  stair::scrollSpeed = 1.0;

  // Creates a random number generator (based on time)
  srand (time(NULL));

  // Load images
  if(!(stair::image = load_bitmap( "images/stairs.png", NULL))){
    abort_on_error( "Cannot find image images/stairs.png \n Please check your files and try again");
  }
  if(!(player::image[0] = load_bitmap( "images/player_1.png", NULL))){
    abort_on_error( "Cannot find image images/player.png \n Please check your files and try again");
  }
  if(!(player::image[1] = load_bitmap( "images/player_2.png", NULL))){
    abort_on_error( "Cannot find image images/player.png \n Please check your files and try again");
  }
  if(!(player::image[2] = load_bitmap( "images/player_3.png", NULL))){
    abort_on_error( "Cannot find image images/player.png \n Please check your files and try again");
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
    stair newStair( i, stair::location_y(i));
    allStairs.push_back(newStair);
  }

  // Player
  player1 = new player( (4 * 30) - player::image[0] -> w, (stair::location_y(4 * 30)) - player::image[0] -> h);
}

// Update game state
void Game::update(){
  // Stairs!
  for( unsigned int i = 0; i < allStairs.size(); i ++ ){
    allStairs.at(i).update( &allStairs);
  }

  for( unsigned int i = 0; i < allStairs.size(); i ++ ){
    allStairs.at(i).movement();
  }

  // Character
  player1 -> update();
}

// Draw game state
void Game::draw(){
  // Background
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255, 255, 255));

  // Stairs!
  for( unsigned int i = 0; i < allStairs.size(); i ++ ){
    // Draw
    allStairs.at(i).draw( buffer);
  }

  // Character
  player1 -> draw( buffer);

  // Buffer
  draw_sprite( screen, buffer, 0, 0);
}

// Destroy
Game::~Game(){
  // Destroy images
  destroy_bitmap( buffer);

  // Fade out
  highcolor_fade_out(16);

  // Clean up fmod
  FSOUND_Close();
}
