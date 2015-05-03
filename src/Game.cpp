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
  if(!switch_flicked)climb_time += 0.1;
}
END_OF_FUNCTION(gameTimer)


// All stairs
vector<stair> allStairs;

void Game::init(){


  // Setup for FPS system
  LOCK_VARIABLE(timer1);
  LOCK_FUNCTION(gameTicker);
  install_int_ex(gameTicker, BPS_TO_TIMER(10));

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
  if(!(stair::image = load_bitmap( ("images/stairs/" + levelOn + "/stairs.png").c_str(), NULL))){
    abort_on_error( ("Cannot find image images/stairs/" + levelOn + "/stairs.png \n Please check your files and try again").c_str());
  }
  if(!(stair::stage_end_red = load_bitmap( ("images/stairs/" + levelOn + "/stage_end_red.png").c_str(), NULL))){
    abort_on_error( ("Cannot find image images/stairs/" + levelOn + "/stage_end_red.png \n Please check your files and try again").c_str());
  }
  if(!(stair::stage_end_green = load_bitmap( ("images/stairs/" + levelOn + "/stage_end_green.png").c_str(), NULL))){
    abort_on_error( ("Cannot find image images/stairs/" + levelOn + "/stage_end_green.png \n Please check your files and try again").c_str());
  }

  if(!(stair::image_brick = load_bitmap( ("images/stairs/" + levelOn + "/brick.png").c_str(), NULL))){
    abort_on_error( ("Cannot find image images/stairs/" + levelOn + "/brick.png \n Please check your files and try again").c_str());
  }
  //Player
  for( int i = 0; i < 8; i++){
    if(!(player::image[i] = load_bitmap( ("images/player/player_" + convertIntToString(i+1) + ".png").c_str(), NULL))){
      abort_on_error( ("Cannot find image images/player/player_" + convertIntToString(i+1) + ".png \n Please check your files and try again").c_str());
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
  // Buttons
  if(!(key_manager::keys[0] = load_bitmap( "images/keys/joy_a.png", NULL))){
    abort_on_error( "Cannot find image images/keys/joy_a.png \n Please check your files and try again");
  }
  if(!(key_manager::keys[3] = load_bitmap( "images/keys/joy_y.png", NULL))){
    abort_on_error( "Cannot find image images/keys/joy_y.png \n Please check your files and try again");
  }
  if(!(key_manager::keys[2] = load_bitmap( "images/keys/joy_x.png", NULL))){
    abort_on_error( "Cannot find image images/keys/joy_x.png \n Please check your files and try again");
  }
  if(!(key_manager::keys[1] = load_bitmap( "images/keys/joy_b.png", NULL))){
    abort_on_error( "Cannot find image images/keys/joy_b.png \n Please check your files and try again");
  }
  if(!(background_sky = load_bitmap( "images/background_sky.png", NULL))){
    abort_on_error( "Cannot find image images/background_sky.png \n Please check your files and try again");
  }
   if(!(background_buildings = load_bitmap( "images/background_buildings.png", NULL))){
    abort_on_error( "Cannot find image images/background_buildings.png \n Please check your files and try again");
  }
  if(!(watch = load_bitmap( "images/watch.png", NULL))){
    abort_on_error( "Cannot find image images/watch.png \n Please check your files and try again");
  }

  // Sounds
  if(!(key_manager::sounds[0] = load_sample("sounds/trip.wav"))){
    abort_on_error( "Cannot find sound sounds/trip.wav \n Please check your files and try again");
  }

  if(!(key_manager::sounds[1] = load_sample("sounds/ping.wav"))){
    abort_on_error( "Cannot find sound sounds/ping.wav \n Please check your files and try again");
  }


  // Other Sprites
  buffer = create_bitmap( SCREEN_W, SCREEN_H);
  stair_buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Temporary fonts
  FONT *f1, *f2, *f3, *f4, *f5;

  //Sets Font
  if(!(f1 = load_font(("fonts/dosis.pcx"), NULL, NULL))){
    abort_on_error( "Cannot find font fonts/dosis.pcx \n Please check your files and try again");
  }

  f2 = extract_font_range(f1, ' ', 'A'-1);
  f3 = extract_font_range(f1, 'A', 'Z');
  f4 = extract_font_range(f1, 'Z'+1, 'z');

  //Merge fonts
  font = merge_fonts(f4, f5 = merge_fonts(f2, f3));


  if(!(f1 = load_font(("fonts/dosis_26.pcx"), NULL, NULL))){
    abort_on_error( "Cannot find font fonts/dosis_26.pcx \n Please check your files and try again");
  }

  f2 = extract_font_range(f1, ' ', 'A'-1);
  f3 = extract_font_range(f1, 'A', 'Z');
  f4 = extract_font_range(f1, 'Z'+1, 'z');

  //Merge fonts
  dosis_26 = merge_fonts(f4, f5 = merge_fonts(f2, f3));


  //Destroy temporary fonts
  destroy_font(f1);
  destroy_font(f2);
  destroy_font(f3);
  destroy_font(f4);
  destroy_font(f5);

  // Stairs (offset is 30 px)
  for( int i = SCREEN_W/4; i < SCREEN_W; i += 30 ){
    stair newStair( i, stair::location_y(i),0);
    allStairs.push_back(newStair);
  }

  // Keys
  screen_keys = new key_manager( 20, 50);

  // Player
  player1 = new player( (10 * 30), (stair::location_y(10 * 30)) - player::image[0] -> h/2);
}

// Update game state
void Game::update(){

  poll_joystick();

  if(!switch_flicked)distance_travelled += stair::scrollSpeed/25;
  if( player1->getY() <= (stair::locationOfFinal - (player1->image[0] -> h - 60))){
    for(int i=0; i<allStairs.size();  i++){
      if(allStairs.at(i).getType()==1)
        allStairs.at(i).setType(2);
    }
  }

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

  if( distance_travelled > level_distance && !is_game_done){
    is_game_done = true;
  }
  if( distance_travelled > level_distance+16){
    switch_flicked = true;
  }

  // Character
  player1 -> update();

  player::animation_frame = int(timer1 * ceil(stair::scrollSpeed)) % 8;

  // Update goats
  for( int i = 0; i < goats.size(); i++)
    goats.at(i).update();

   // Motherfing goats!
  if( random( 0, 100) == 0){
    float randomDistance = float(random( 2, 6))/10;
    goat newGoat(SCREEN_W, random( 0, SCREEN_H), randomDistance, randomDistance*3);
    goats.push_back( newGoat);
  }


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
   // Draw goats
  for( int i = 0; i < goats.size(); i++)
    goats.at(i).draw( buffer);

  // Stairs!
  rectfill( stair_buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255, 0, 255));
  for( unsigned int i = 0; i < allStairs.size(); i ++ ){
    // Draw
    allStairs.at(i).draw( stair_buffer);
  }
  draw_sprite( buffer, stair_buffer, 0, 0);

  // Character
  player1 -> draw( buffer);

  // Key manager
  if(!switch_flicked)screen_keys -> draw( buffer);

  // Timer
  rectfill(buffer,20,20,620,80,makecol(0,0,0));
  rectfill(buffer,24,24,616,76,makecol(255,255,255));
  if(is_game_done)rectfill(buffer,24,24,616,76,makecol(0,255,0));
  if(!is_game_done)rectfill(buffer,24,24,24+(600*(distance_travelled/level_distance)),76,makecol(0,255,0));


  if(!is_game_done)textprintf_ex( buffer, font, 20,32, makecol(0,0,0), -1, "%4.0f/%i", distance_travelled,level_distance);
  if(is_game_done)textprintf_ex( buffer, font, 40,32, makecol(0,0,0), -1, "%i/%i",level_distance,level_distance);

  set_alpha_blender();
  draw_trans_sprite(buffer,watch,SCREEN_W-100,SCREEN_H-70);
  textprintf_ex( buffer, dosis_26, SCREEN_W-75,SCREEN_H-60, makecol(255,255,255), -1, "%4.1f", climb_time);



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
