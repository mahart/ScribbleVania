// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <d3dx9math.h>


//===============================================
// New Stuff
//===============================================
const float MAX_PLAYER_SPEED = 200.0f;
const float MAX_RED_SNAIL_MOVE_SPEED = 50.0f;
const float MAX_RED_SNAIL_ATTACK_SPEED = 250.0f;
const D3DXVECTOR3 ZERO_VECTOR  = D3DXVECTOR3(0,0,0);
const float BORING_P_BASE_SPEED = 500.0f;


const int RED_SNAIL_COLS=8;
const int RED_SNAIL_WIDTH= 50;
const int RED_SNAIL_HEIGHT = 44;
const float RED_SNAIL_ANIMATION_DELAY = 0.2f; 
const int  RED_SNAIL_START_FRAME_RIGHT = 0;
const int RED_SNAIL_END_FRAME_RIGHT = 7;
const int RED_SNAIL_START_FRAME_LEFT=8;
const int RED_SNAIL_END_FRAME_LEFT=15;
const int RED_SNAIL_AGGRO_RADIUS=250;
const int RED_SNAIL_PATROL_ACCEL = 100000;
const int RED_SNAIL_ATTACK_ACCEL = 300000;


const int GRAY_SNAIL_COLS=8;
const int GRAY_SNAIL_WIDTH = 50;
const int GRAY_SNAIL_HEIGHT = 44;
const float GRAY_SNAIL_ANIMATION_DELAY = 0.2f; 
const int  GRAY_SNAIL_START_FRAME_RIGHT = 0;
const int GRAY_SNAIL_END_FRAME_RIGHT = 7;
const int GRAY_SNAIL_START_FRAME_LEFT=8;
const int GRAY_SNAIL_SHOT_FRAME1 = 6;
const int GRAY_SNAIL_SHOT_FRAME2 = 9;
const int GRAY_SNAIL_END_FRAME_LEFT=15;
const int GRAY_SNAIL_AGGRO_RADIUS=250;
const int GRAY_SNAIL_PATROL_ACCEL = 100000;

const int SNAIL_BOSS_COLS=8;
const int SNAIL_BOSS_WIDTH=50;
const int SNAIL_BOSS_SHOT_LEFT_START=0;
const int SNAIL_BOSS_SHOT_LEFT_END=0;
const int SNAIL_BOSS_SHOT_RIGHT_START=0;
const int SNAIL_BOSS_SHOT_RIGHT_END=0;
const float SNAIL_BOSS_SHOT_ANIMATION_DELAY=0.1f;
const int SNAIL_BOSS_HEIGHT=44;
const int SNAIL_BOSS_START_FRAME=0;
const int SNAIL_BOSS_START_FRAME_STANDING_RIGHT=0;
const int SNAIL_BOSS_END_FRAME_STANDING_RIGHT=7;
const int SNAIL_BOSS_START_FRAME_STANDING_LEFT=24;
const int SNAIL_BOSS_END_FRAME_STANDING_LEFT=31;
const int SNAIL_BOSS_START_FRAME_BOUNCING_RIGHT=8;
const int SNAIL_BOSS_END_FRAME_BOUNCING_RIGHT=15;
const int SNAIL_BOSS_START_FRAME_BOUNCING_LEFT=16;
const int SNAIL_BOSS_END_FRAME_BOUNCING_LEFT=23;
const int SNAIL_BOSS_END_FRAME=7;
const float SNAIL_BOSS_ANIMATION_DELAY = 0.1f;
//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(255,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
// KEYS
//-----------------------------------------------
#define VK_W  0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
#define VK_J 0x4A;


//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  // photo source NASA/courtesy of nasaimages.org 
const char TEST_BG[]="pictures\\ws_Abstract.jpg";
const char TEST_BG_2[] = "pictures\\background_2d_couleur_by_echodesigngarden-d5mwv69.jpg";
const char PLANET_IMAGE[] = "pictures\\planet.png"; // picture of planet
const char SHIP_IMAGE[]   = "pictures\\ship.png";   // spaceship
const char BOX_IMAGE[] = "pictures\\BoundingBox.png";//Bounding box 
const char LEDGE_IMAGE[] = "pictures\\LedgeBox.png";//LedgeBox
const char RED_SNAIL_IMAGE[] = "pictures\\super_metroid_yard3.png";//RED_SNAIL Enemy
const char GRAY_SNAIL_IMAGE[] = "pictures\\super_metroid_yard2.png";//GRAY_SNAIL Enemy
const char SNAIL_BOSS_IMAGE[] = "pictures\\super_metroid_yard-Boss.png";//Snail boss
const char OPEN_DOOR_IMAGE[] = "pictures\\OpenDoor.png";
const char CIRCLE_IMAGE[] = "pictures\\BoundingCircle.png";
const char BASIC_SHOT_IMAGE[] = "pictures\\Shot.png";

// window
const char CLASS_NAME[] = "ScribbleVania";
const char GAME_TITLE[] = "ScribbleVania";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1280;               // width of game in pixels
const UINT GAME_HEIGHT = 720;               // height of game in pixels
const int  SHIP_START_FRAME = 0;            // starting frame of ship animation
const int  SHIP_END_FRAME = 3;              // last frame of ship animation
const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames of ship animation
const int  SHIP_COLS = 2;                   // ship texture has 2 columns
const int  SHIP_WIDTH = 32;                 // width of ship image
const int  SHIP_HEIGHT = 32;                // height of ship image
const float ROTATION_RATE = 180.0f;         // degrees per second
const float SCALE_RATE = 0.2f;              // % change per second
const float SHIP_SPEED = 100.0f;            // pixels per second
const float SHIP_SCALE = 1.5f;              // starting ship scale
const int PLAYER_ACCEL = 250000;

// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 981000;

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR PLAYER_LEFT_KEY    = VK_A;     // left arrow
const UCHAR PLAYER_RIGHT_KEY   = VK_D;    // right arrow
const UCHAR PLAYER_SHOOT_KEY   = VK_J;
const UCHAR PLAYER_UP_KEY      = VK_W;       // up arrow
const UCHAR PLAYER_JUMP_KEY	   = VK_SPACE;	//spacebar
const UCHAR PLAYER_DOWN_KEY    = VK_S;     // down arrow

