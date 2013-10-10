// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

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
//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char NEBULA_IMAGE[] = "pictures\\orion.jpg";  // photo source NASA/courtesy of nasaimages.org 
const char PLANET_IMAGE[] = "pictures\\planet.png"; // picture of planet
const char SHIP_IMAGE[]   = "pictures\\ship.png";   // spaceship
const char BOX_IMAGE[] = "pictures\\BoundingBox.png";//Bounding box 
const char CIRCLE_IMAGE[] = "pictures\\BoundingCircle.png";

// window
const char CLASS_NAME[] = "ScribbleVania";
const char GAME_TITLE[] = "ScribbleVania";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels
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

// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR SHIP_LEFT_KEY    = VK_A;     // left arrow
const UCHAR SHIP_RIGHT_KEY   = VK_D;    // right arrow
const UCHAR SHIP_UP_KEY      = VK_W;       // up arrow
const UCHAR SHIP_DOWN_KEY    = VK_S;     // down arrow

