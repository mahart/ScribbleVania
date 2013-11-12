// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 ScribbleVania.h v1.0

#pragma once
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "../Graphic/TextureManager.h"
#include "../Graphic/Image.h"
#include "../GameObject/Player/Player.h"
#include "../GameObject/EnvironmentObject.h"
#include "../ObjectManager.h"
//=============================================================================
// This class is the core of the game
//=============================================================================
class ScribbleVania : public Game
{
private:
	ObjectManager *_manager;
    // game items
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

