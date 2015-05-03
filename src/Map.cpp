#include "Map.h"

Map::Map()
{
  // Create buffer image
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Load music
  if(!(music = FSOUND_Stream_Open("music/the-experiment.mp3",2, 0, 0))){
    abort_on_error( "Cannot find music music/the-experiment.mp3 \n Please check your files and try again");
  }

  // Load images
  if(!(map_image = load_bitmap("images/map/map.png", NULL))){
    abort_on_error( "Cannot find image images/map/map.png \n Please check your files and try again");
  }
  if(!(cursor = load_bitmap("images/map/cursor.png", NULL))){
    abort_on_error( "Cannot find image images/map/cursor.png \n Please check your files and try again");
  }


  // Locations
  if(!(location::pin_image = load_bitmap("images/map/pin.png", NULL))){
    abort_on_error( "Cannot find image images/map/pin.png \n Please check your files and try again");
  }

   // Locations
  if(!(location::pin_grey_image = load_bitmap("images/map/pin_grey.png", NULL))){
    abort_on_error( "Cannot find image images/map/pin_grey.png \n Please check your files and try again");
  }

  // Allow transparency
  set_alpha_blender();

  // Clear mapLocations
  mapLocations.clear();

  // Add locations
  location cn_tower( 224, 210, "images/map/icon_cntower.png", "cn_tower");
  mapLocations.push_back( cn_tower);

  location pyramids( 418, 243, "images/map/icon_pyramids.png", "pyramids");
  mapLocations.push_back( pyramids);

  location statue_of_liberty( 236, 216, "images/map/icon_statueofliberty.png", "statue_of_liberty");
  mapLocations.push_back( statue_of_liberty);

  location stone_henge( 356, 193, "images/map/icon_stonehenge.png", "stone_henge");
  mapLocations.push_back( stone_henge);

  location taj_mahal( 503, 250, "images/map/icon_tajmahal.png", "taj_mahal");
  mapLocations.push_back( taj_mahal);

  location wall_of_china( 570, 217, "images/map/icon_wallofchina.png", "wall_of_china");
  mapLocations.push_back( wall_of_china);

  // Cursor position
  position_mouse( SCREEN_W / 2, SCREEN_H / 2);

  // Start music
  FSOUND_Stream_Play( 0, music);
}

void Map::update(){
  // Update joystick
  poll_joystick();

  // Change level
  if( mouse_b & 1 || (joystick_enabled && joy[0].button[0].b)){
    for( unsigned int i = 0; i < mapLocations.size(); i++){
      if( mapLocations.at(i).CheckHover()){
        levelOn = mapLocations.at(i).getName();
        set_next_state( STATE_GAME);
      }
    }
  }


  // Move cursor
  if( joystick_enabled){
    position_mouse(mouse_x+(joy[0].stick[0].axis[0].pos/30),mouse_y+(joy[0].stick[0].axis[1].pos/20));

  }

  // Back to menu
  if( key[KEY_M])
    set_next_state( STATE_MENU);
}

void Map::draw(){
  // Draw background to screen
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255,255,255));

  // Map image
  draw_sprite( buffer, map_image, 0, 0);

  // Locations
  for( unsigned int i = 0; i < mapLocations.size(); i++){
     mapLocations.at(i).draw( buffer);
  }

  // Cursor
  draw_sprite( buffer, cursor, mouse_x - cursor -> w / 2, mouse_y - cursor -> h / 2);

  // Draw Buffer
  draw_sprite( screen, buffer, 0, 0);
}

Map::~Map(){
  // Destory Bitmaps
  destroy_bitmap(buffer);
  destroy_bitmap(map_image);
  destroy_bitmap(cursor);
  mapLocations.clear();
  destroy_bitmap(location::pin_image);

  // Stop music
  FSOUND_Stream_Stop(music);

  // Fade out
  highcolor_fade_out(16);
}
