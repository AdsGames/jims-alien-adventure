#include "Menu.h"

Menu::Menu(){
  // Create buffer image
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Load music
  if(!(music = FSOUND_Stream_Open("music/JAA-Theme.mp3",2, 0, 0))){
      abort_on_error( "Cannot find music music/JAA-Theme.mp3 \n Please check your files and try again");
  }

  // Load images
  if(!(background[0] = load_bitmap("images/menu/menu.png", NULL))){
      abort_on_error( "Cannot find image images/menu/menu.png \n Please check your files and try again");
  }
  if(!(background[1] = load_bitmap("images/menu/menu_2.png", NULL))){
      abort_on_error( "Cannot find image images/menu/menu_2.png \n Please check your files and try again");
  }
  if(!(title = load_bitmap("images/menu/title.png", NULL))){
      abort_on_error( "Cannot find image images/menu/title.png \n Please check your files and try again");
  }
  if(!(sky = load_bitmap("images/background_sky.png", NULL))){
      abort_on_error( "Cannot find image images/background_sky.png \n Please check your files and try again");
  }
  if(!(city = load_bitmap("images/background_buildings.png", NULL))){
      abort_on_error( "Cannot find image images/background_buildings.png \n Please check your files and try again");
  }
  if(!(cursor = load_bitmap("images/menu/cursor1.png", NULL))){
      abort_on_error( "Cannot find image images/menu/cursor1.png \n Please check your files and try again");
  }
  if(!(goat::goat_image[0] = load_bitmap("images/goat_alien.png", NULL))){
      abort_on_error( "Cannot find image images/goat_alien.png \n Please check your files and try again");
  }
  if(!(goat::goat_image[1] = load_bitmap("images/goat_alien_2.png", NULL))){
      abort_on_error( "Cannot find image images/goat_alien_2.png \n Please check your files and try again");
  }
  if(!(little_xbox_buttons = load_bitmap("images/menu/angle_buttons.png", NULL))){
    abort_on_error( "Cannot find image images/menu/angle_buttons.png \n Please check your files and try again");
  }

  // Temporary fonts
  FONT *f1, *f2, *f3, *f4, *f5;

  //Sets Font
  if(!(f1 = load_font(("fonts/dosis.pcx"), NULL, NULL))){
    abort_on_error( "Cannot find font fonts/dosis.png \n Please check your files and try again");
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

  // Allow transparency
  set_alpha_blender();

  // Variable set
  title_y = -title -> h;
  city_x = 0;
  switchFlipped = false;

  // Buttons
  start = new Button( "images/menu/button_play.png", "images/menu/button_pushed_play.png", 30, 190);
  story = new Button( "images/menu/button_story.png", "images/menu/button_pushed_story.png", 195, 190);
  options = new Button( "images/menu/button_options.png", "images/menu/button_pushed_options.png", 30, 300);
  exit = new Button( "images/menu/button_exit.png", "images/menu/button_pushed_exit.png", 195, 300);

  FSOUND_Stream_Play(0,music);
}

void Menu::update(){
  // Poll joystick
  poll_joystick();

  // Drop title
  if( title_y < 20)
    title_y += (20 - title_y)/80;
  else{
    title_y = 100;
  }

  // Move city
  if( city_x < -city -> w)
    city_x = city_x + city -> w;
  else
    city_x -= 2;


  // Buttons
  if( (start -> CheckHover() && mouse_b & 1) || (joystick_enabled && joy[0].button[0].b))
    set_next_state( STATE_MAP);
  if( (story -> CheckHover() && mouse_b & 1) || (joystick_enabled && joy[0].button[2].b))
    set_next_state(STATE_STORY);
  if( (exit -> CheckHover() && mouse_b & 1) || (joystick_enabled && joy[0].button[1].b))
    set_next_state(STATE_EXIT);

  // Motherfing goats!
  if( random( 0, 100) == 0){
    float randomDistance = float(random( 2, 6))/10;
    goat newGoat(SCREEN_W, random( 0, SCREEN_H), randomDistance, randomDistance*3);
    goats.push_back( newGoat);
  }

  // Update goats
  for( unsigned int i = 0; i < goats.size(); i++){
    // Update
    goats.at(i).update();
    // Make them fall
    if( switchFlipped)
      goats.at(i).fall(5);
    // Destroy goat
    if( goats.at(i).kill())
      goats.erase( goats.begin() + i);
  }

  // Flip switch
  if( mouse_b & 1){
    if( (!switchFlipped && collisionAny( 595, 607, mouse_x, mouse_x, 236, 248, mouse_y, mouse_y)) || (switchFlipped && collisionAny( 579, 591, mouse_x, mouse_x, 235, 247, mouse_y, mouse_y))){
      switchFlipped = !switchFlipped;
    }
  }
}

void Menu::draw(){
  // Draw background to screen
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255,255,255));

  // Sky
  stretch_sprite( buffer, sky, 0, 0, SCREEN_W, SCREEN_H);

  // City scroll
  draw_sprite( buffer, city, city_x, SCREEN_H - city -> h);
  draw_sprite( buffer, city, city_x + city -> w, SCREEN_H - city -> h);

  // Draw goats
  for( unsigned int i = 0; i < goats.size(); i++)
    goats.at(i).draw( buffer);

  // Stairs
  draw_sprite( buffer, background[switchFlipped], 0, 0);

  // Title
  draw_trans_sprite( buffer, title, 20, title_y);

  // Buttons
  start -> draw( buffer);
  story -> draw( buffer);
  options -> draw( buffer);
  exit -> draw( buffer);

  // Joystick helpers
  if( joystick_enabled){
    masked_blit( little_xbox_buttons, buffer, 60, 0, start   -> GetX() + 25 - 4 * start   -> CheckHover(), start   -> GetY() + 114 - start   -> CheckHover(), 20, 20);
    masked_blit( little_xbox_buttons, buffer, 40, 0, story   -> GetX() + 25 - 4 * story   -> CheckHover(), story   -> GetY() + 114 - story   -> CheckHover(), 20, 20);
    masked_blit( little_xbox_buttons, buffer, 0 , 0, options -> GetX() + 25 - 4 * options -> CheckHover(), options -> GetY() + 114 - options -> CheckHover(), 20, 20);
    masked_blit( little_xbox_buttons, buffer, 20, 0, exit    -> GetX() + 25 - 4 * exit    -> CheckHover(), exit    -> GetY() + 114 - exit    -> CheckHover(), 20, 20);
  }

  // Cursor
  draw_sprite( buffer, cursor, mouse_x, mouse_y);

  // Draw Buffer
  draw_sprite( screen, buffer, 0, 0);
}

Menu::~Menu(){
  // Destory Bitmaps
  destroy_bitmap(buffer);
  destroy_bitmap(title);
  destroy_bitmap(sky);
  destroy_bitmap(city);
  destroy_bitmap(cursor);
  destroy_bitmap(background[0]);
  destroy_bitmap(background[1]);
  destroy_bitmap( goat::goat_image[0]);
  destroy_bitmap( goat::goat_image[1]);

  // Kill pointers
  delete start;
  delete story;
  delete options;
  delete exit;

  // Clear away goats
  goats.clear();

  // Stop music
  FSOUND_Stream_Stop(music);

  // Clear keybuff
  clear_keybuf();

  // Fade out
  highcolor_fade_out(32);
}
