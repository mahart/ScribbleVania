// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 ScribbleVania.h v1.0

#ifndef _SCRIBBLE_VANIA_H             // Prevent multiple definitions if this 
#define _SCRIBBLE_VANIA_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "Player.h"
#include "EnvironmentObject.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class ScribbleVania : public Game
{
private:
    // game items
    TextureManager nebulaTexture;   // nebula texture
    TextureManager planetTexture;   // planet texture
    TextureManager shipTexture;     // ship texture
    Image   nebula;                 // nebula image
	EnvironmentObject* background;
	Player* player;
	EnvironmentObject* eo;

public:
    // Constructor
    ScribbleVania();

    // Destructor
    virtual ~ScribbleVania();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
