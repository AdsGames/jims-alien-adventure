#include "Map.h"

Map::Map()
{
  // Init fmod
  FSOUND_Init (44100, 32, 0);

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
  if(!(cursor = load_bitmap("images/menu/cursor1.png", NULL))){
    abort_on_error( "Cannot find image images/menu/cursor1.png \n Please check your files and try again");
  }

  // Locations
  if(!(location::pin_image = load_bitmap("images/map/pin.png", NULL))){
    abort_on_error( "Cannot find image images/map/pin.png \n Please check your files and try again");
  }
  if(!(locationImages[0] = load_bitmap("images/map/icon_cntower.png", NULL))){
    abort_on_error( "Cannot find image images/map/icon_cntower.png \n Please check your files and try again");
  }
  if(!(locationImages[1] = load_bitmap("images/map/icon_pyramids.png", NULL))){
    abort_on_error( "Cannot find image images/map/icon_pyramids.png \n Please check your files and try again");
  }
  if(!(locationImages[2] = load_bitmap("images/map/icon_statueofliberty.png", NULL))){
    abort_on_error( "Cannot find image images/map/icon_statueofliberty.png \n Please check your files and try again");
  }
  if(!(locationImages[3] = load_bitmap("images/map/icon_stonehenge.png", NULL))){
    abort_on_error( "Cannot find image images/map/icon_stonehenge.png \n Please check your files and try again");
  }
  if(!(locationImages[4] = load_bitmap("images/map/icon_tajmahal.png", NULL))){
    abort_on_error( "Cannot find image images/map/icon_tajmahal.png \n Please check your files and try again");
  }
  if(!(locationImages[5] = load_bitmap("images/map/icon_wallofchina.png", NULL))){
    abort_on_error( "Cannot find image images/map/icon_cntower.png \n Please check your files and try again");
  }

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

  // Allow transparency
  set_alpha_blender();

  FSOUND_Stream_Play( 0, music);

  // Add locations
  location cn_tower( 224, 210, locationImages[0], "cn_tower");
  mapLocations.push_back( cn_tower);

  location pyramids( 418, 243, locationImages[1], "pyramids");
  mapLocations.push_back( pyramids);

  location statue_of_liberty( 236, 216, locationImages[2], "statue_of_liberty");
  mapLocations.push_back( statue_of_liberty);

  location stone_henge( 356, 193, locationImages[3], "stone_henge");
  mapLocations.push_back( stone_henge);

  location taj_mahal( 503, 250, locationImages[4], "taj_mahal");
  mapLocations.push_back( taj_mahal);

  location wall_of_china( 570, 217, locationImages[5], "wall_of_china");
  mapLocations.push_back( wall_of_china);
}

void Map::update(){
  // Change level
  if( mouse_b & 1){
    for( unsigned int i = 0; i < mapLocations.size(); i++){
      if( mapLocations.at(i).CheckHover()){
        levelOn = mapLocations.at(i).getName();
        set_next_state( STATE_GAME);
      }
    }
  }
}

void Map::draw(){
  // Draw background to screen
  rectfill( buffer, 0, 0, SCREEN_W, SCREEN_H, makecol( 255,255,255));

  // Map image
  draw_sprite( buffer, map_image, 0, 0);

  // Locations
  for( int i = 0; i < mapLocations.size(); i++)
    mapLocations.at(i).draw( buffer);

  // Cursor
  draw_sprite( buffer, cursor, mouse_x, mouse_y);

  // Draw Buffer
  draw_sprite( screen, buffer, 0, 0);
}

Map::~Map(){
  // Destory Bitmaps
  destroy_bitmap( buffer);

  // Fade out
  highcolor_fade_out(16);

  // Stop music
  FSOUND_Stream_Stop(music);

  // Clean up fmod
  FSOUND_Close();
}
