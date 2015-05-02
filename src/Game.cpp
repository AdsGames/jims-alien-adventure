#include "Game.h"

volatile int Game::timer1 = 00;
volatile float Game::climb_time = 00;

Game::Game()
{
  // Init
  init();
}

void Game::gameTicker(){
  timer1++;
}
END_OF_FUNCTION(gameTicker)

void Game::gameTimer(){
  climb_time += 0.1;
}
END_OF_FUNCTION(gameTimer)


// All stairs
vector<stair> allStairs;

void Game::init(){
  // Setup for FPS system
  LOCK_VARIABLE(timer1);
  LOCK_FUNCTION(gameTicker);
  install_int_ex(gameTicker, BPS_TO_TIMER(5));

  // Timer!
  LOCK_VARIABLE(climb_time);
  LOCK_FUNCTION(gameTimer);
  install_int_ex(gameTimer, BPS_TO_TIMER(10));

  // Init fmod
  FSOUND_Init (44100, 32, 0);

  // Init variables
  stair::scrollSpeed = 0;

  // Creates a random number generator (based on time)
  srand (time(NULL));

  // Load images
  if(!(stair::image = load_bitmap( "images/stairs.png", NULL))){
    abort_on_error( "Cannot find image images/stairs.png \n Please check your files and try again");
  }
  if(!(stair::image_brick = load_bitmap( "images/brick.png", NULL))){
    abort_on_error( "Cannot find image images/brick.png \n Please check your files and try again");
  }
  //Player
  for( int i = 0; i < 7; i++){
    if(!(player::image[i] = load_bitmap( ("images/player_" + convertIntToString(i+1) + ".png").c_str(), NULL))){
      abort_on_error( ("Cannot find image images/player_" + convertIntToString(i+1) + ".png \n Please check your files and try again").c_str());
    }
  }
  // Keys
  if(!(key_manager::keys[KEY_UP] = load_bitmap( "images/keys/key_up.png", NULL))){
    abort_on_error( "Cannot find image images/keys/key_up.png \n Please check your files and try again");
  }
  if(!(key_manager::keys[KEY_DOWN] = load_bitmap( "images/keys/key_down.png", NULL))){
    abort_on_error( "Cannot find image images/keys/key_down.png \n Please check your files and try again");
  }
  if(!(key_manager::keys[KEY_LEFT] = load_bitmap( "images/keys/key_left.png", NULL))){
    abort_on_error( "Cannot find image images/keys/key_left.png \n Please check your files and try again");
  }
  if(!(key_manager::keys[KEY_RIGHT] = load_bitmap( "images/keys/key_right.png", NULL))){
    abort_on_error( "Cannot find image images/keys/key_right.png \n Please check your files and try again");
  }
  if(!(background_sky = load_bitmap( "images/background_sky.png", NULL))){
    abort_on_error( "Cannot find image images/background_sky.png \n Please check your files and try again");
  }
   if(!(background_buildings = load_bitmap( "images/background_buildings.png", NULL))){
    abort_on_error( "Cannot find image images/background_buildings.png \n Please check your files and try again");
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
  for( int i = SCREEN_W/2; i < SCREEN_W; i += 30 ){
    stair newStair( i, stair::location_y(i));
    allStairs.push_back(newStair);
  }

  // Keys
  screen_keys = new key_manager( 20, 20);

  // Player
  player1 = new player( (20 * 30) - player::image[0] -> w/2, (stair::location_y(20 * 30)) - player::image[0] -> h/2);
}

// Update game state
void Game::update(){
  // Scroll background
  background_scroll -= stair::scrollSpeed/4;
  if(background_scroll < 0)
    background_scroll = 1024;

  // Stairs!
  for( unsigned int i = 0; i < allStairs.size(); i ++ ){
    allStairs.at(i).update( &allStairs);
  }

  for( unsigned int i = 0; i < allStairs.size(); i ++ ){
    allStairs.at(i).movement();
  }

  // Character
  player1 -> update();

  player::animation_frame = int(timer1 * ceil(stair::scrollSpeed)) % 7;

  // Key manager
  screen_keys -> update();
}

// Draw game state
void Game::draw(){
  // Background
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255, 255, 255));
  stretch_sprite(buffer,background_sky, 0, 0, SCREEN_W, SCREEN_H);
  draw_sprite(buffer,background_buildings,0+background_scroll,SCREEN_H-270);
  draw_sprite(buffer,background_buildings,-1024 + background_scroll,SCREEN_H-270);

  // Stairs!
  for( unsigned int i = 0; i < allStairs.size(); i ++ ){
    // Draw
    allStairs.at(i).draw( buffer);
  }

  // Character
  player1 -> draw( buffer);

  // Key manager
  screen_keys -> draw( buffer);

  // Timer
  textprintf_ex( buffer, font, 20, 120, makecol(0,0,0), -1, "Time:%4.1f", climb_time);

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
