#include "Game.h"

volatile int Game::timer1 = 0;
volatile float Game::climb_time = 0;
volatile float Game::time_since_win = 0;

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
  if(!switch_flicked)
    climb_time += 0.1;
}
END_OF_FUNCTION(gameTimer)

void Game::endTimer(){
  time_since_win += 0.1;
}
END_OF_FUNCTION(endTimer)


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

  // Timer!
  LOCK_VARIABLE(time_since_win);
  LOCK_FUNCTION(endTimer);

  // Creates a random number generator (based on time)
  srand (time(NULL));

  // Load music
  if(!(mainMusic = FSOUND_Stream_Open("music/JAA-Ingame.mp3",2, 0, 0))){
    abort_on_error( "Cannot find music music/JAA-Ingame.mp3 \n Please check your files and try again");
  }

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
  if(!(background_sky = load_bitmap( ("images/stairs/" + levelOn + "/sky.png").c_str(), NULL))){
    abort_on_error( ("Cannot find image images/stairs/" + levelOn + "/sky.png \n Please check your files and try again").c_str());
  }
   if(!(background_buildings = load_bitmap( ("images/stairs/" + levelOn + "/parallax.png").c_str(), NULL))){
    abort_on_error( ("Cannot find image images/stairs/" + levelOn + "/parallax.png \n Please check your files and try again").c_str());
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
  if(!(watch = load_bitmap( "images/watch.png", NULL))){
    abort_on_error( "Cannot find image images/watch.png \n Please check your files and try again");
  }
   if(!(youwin = load_bitmap("images/youwin.png", NULL))){
    abort_on_error( "Cannot find image images/youwin.png \n Please check your files and try again");
  }
  // Goat
  if(!(goat::goat_image[0] = load_bitmap("images/goat_alien.png", NULL))){
      abort_on_error( "Cannot find image images/goat_alien.png \n Please check your files and try again");
  }
  if(!(goat::goat_image[1] = load_bitmap("images/goat_alien_2.png", NULL))){
      abort_on_error( "Cannot find image images/goat_alien_2.png \n Please check your files and try again");
  }
  // Sounds
  if(!(key_manager::sounds[0] = load_sample("sounds/trip.wav"))){
    abort_on_error( "Cannot find sound sounds/trip.wav \n Please check your files and try again");
  }
  if(!(key_manager::sounds[1] = load_sample("sounds/ping.wav"))){
    abort_on_error( "Cannot find sound sounds/ping.wav \n Please check your files and try again");
  }

   if(!(win = load_sample("sounds/win.wav"))){
    abort_on_error( "Cannot find sound sounds/win.wav \n Please check your files and try again");
  }
   if(!(lose = load_sample("sounds/lose.wav"))){
    abort_on_error( "Cannot find sound sounds/lose.wav \n Please check your files and try again");
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

  // Keys
  screen_keys = new key_manager( 20, 50);

  // Player
  player1 = new player( (10 * 30), (stair::location_y(10 * 30)) - player::image[0] -> h/2);

  // LEVEL DIFFICULTY!
  if(levelOn == "cn_tower"){
    level_distance = 0;
    time_to_complete = 40;
  }
  else if(levelOn == "statue_of_liberty"){
    level_distance = 0;
    time_to_complete = 60;
  }
  else if(levelOn == "stone_henge"){
    level_distance = 400;
    time_to_complete = 80;
  }
  else if(levelOn == "taj_mahal"){
    level_distance = 500;
    time_to_complete = 100;
  }
  if(levelOn == "pyramids"){
    level_distance = 600;
    time_to_complete = 120;
  }
  else if(levelOn == "wall_of_china"){
    level_distance = 700;
    time_to_complete = 140;
  }

  // Reset variables
  animationFrame = 0;
  background_scroll = 0.0;
  distance_travelled = 0.0;
  switch_flicked = false;
  distance_is_reached = false;
  stair::final_stair_placed = false;
  stair::locationOfFinal = 0;
  sound_played=false;

  timer1 = 0;
  climb_time = 0;
  time_since_win = 0;

  // Stairs (offset is 30 px)
  for( int i = SCREEN_W/4; i < SCREEN_W; i += 30 ){
    stair newStair( i, stair::location_y(i),0);
    allStairs.push_back(newStair);
  }


  // Init variables
  stair::scrollSpeed = 0;

  // Start music
  FSOUND_Stream_Play( 0, mainMusic);
}

// Update game state
void Game::update(){

  // Joystick input
  poll_joystick();

  // Start timer
  if( (screen_keys -> buttonDown() || screen_keys -> keyDown()) && climb_time <= 0){
    install_int_ex(gameTimer, BPS_TO_TIMER(10));
  }

  // Add to distance until switch is flicked
  if(!switch_flicked)
    distance_travelled += stair::scrollSpeed/25;

  // When you reach destination
  if( (player1 -> getY() <= (stair::locationOfFinal - (player1 -> image[0] -> h))) && stair::final_stair_placed){
    switch_flicked = true;
    for(unsigned int i = 0; i < allStairs.size(); i++){
      if(allStairs.at(i).getType() == 1)
        allStairs.at(i).setType(2);
    }
  }

  // You reached distance for spawning top!
  if( distance_travelled > level_distance && !distance_is_reached){
    distance_is_reached = true;
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

  // Character
  player1 -> update();
  player::animation_frame = int(timer1 * ceil(stair::scrollSpeed)) % 8;

  // Update goats
  for( unsigned int i = 0; i < goats.size(); i++){
    goats.at(i).update();
    if( switch_flicked)
      goats.at(i).fall(6);
  }

  // End game
  if(time_since_win >= 3.0){
    set_next_state( STATE_MENU);
  }
  else if( switch_flicked && time_since_win <= 0){
    install_int_ex(endTimer, BPS_TO_TIMER(10));
  }


   // Motherfing goats!
  if( random( 0, 100) == 0){
    float randomDistance = float(random( 2, 6))/10;
    goat newGoat(SCREEN_W, random( 0, SCREEN_H), randomDistance, randomDistance*3);
    goats.push_back( newGoat);
  }

  // Back to menu
  if( key[KEY_M])
    set_next_state( STATE_MENU);

  if(time_to_complete-climb_time <= 0){
    install_int_ex(endTimer, BPS_TO_TIMER(10));
    climb_time=time_to_complete;
    if(!sound_played){
      play_sample(lose,255,125,1000,0);
      sound_played=true;
      // Stop music
      FSOUND_Stream_Stop(mainMusic);
    }
  }

//set_next_state(STATE_MENU);


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
  for( unsigned int i = 0; i < goats.size(); i++)
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
  if(!switch_flicked)
    screen_keys -> draw( buffer);

  // Timer
  rectfill(buffer,20,20,620,80,makecol(0,0,0));
  rectfill(buffer,24,24,616,76,makecol(255,255,255));
  if(distance_is_reached)
    rectfill(buffer,24,24,616,76,makecol(0,255,0));
  if(!distance_is_reached)
    rectfill(buffer,24,24,24+(600*(distance_travelled/level_distance)),76,makecol(0,255,0));


  if(!distance_is_reached)
    textprintf_ex( buffer, font, 20,32, makecol(0,0,0), -1, "%4.0f/%i", distance_travelled,level_distance);
  if(distance_is_reached)
    textprintf_ex( buffer, font, 40,32, makecol(0,0,0), -1, "%i/%i",level_distance,level_distance);


  if(switch_flicked){
    if(!sound_played){
      play_sample(win,255,125,1000,0);
      sound_played=true;
      // Stop music
      FSOUND_Stream_Stop(mainMusic);
    }
    draw_sprite( buffer, youwin, 200, 200);
  }
  set_alpha_blender();
  draw_trans_sprite(buffer,watch,SCREEN_W-100,SCREEN_H-70);
  if(time_to_complete-climb_time>0)textprintf_ex( buffer, dosis_26, SCREEN_W-75,SCREEN_H-60, makecol(255,255,255), -1, "%4.1f", time_to_complete-climb_time);
  if(time_to_complete-climb_time<=0)textprintf_ex( buffer, dosis_26, SCREEN_W-75,SCREEN_H-60, makecol(255,255,255), -1, "0.0");


  // Buffer
  draw_sprite( screen, buffer, 0, 0);
}

// Destroy
Game::~Game(){
  // Destroy images
  destroy_bitmap(buffer);
  destroy_bitmap(stair_buffer);
  destroy_bitmap(background_sky);
  destroy_bitmap(background_buildings);
  destroy_bitmap(watch);
  destroy_bitmap(youwin);

  // Stair images
  destroy_bitmap( stair::image);
  destroy_bitmap( stair::stage_end_green);
  destroy_bitmap( stair::image_brick);
  destroy_bitmap( stair::stage_end_red);

  // Goats
  destroy_bitmap( goat::goat_image[0]);
  destroy_bitmap( goat::goat_image[1]);

  // Fonts
  destroy_font(dosis_26);

  // Timers
  remove_int( gameTimer);
  remove_int( gameTicker);
  remove_int( endTimer);

  delete screen_keys;
  delete player1;

  goats.clear();
  allStairs.clear();

  // Stop music
  FSOUND_Stream_Stop(mainMusic);

  // Fade out
  highcolor_fade_out(16);
}
