#include "ScribbleVania.h"
#include "GameObject.h"
#include "TestPlanetObj.h"
#include "TestBackground.h"
#include "Room.h"
//=============================================================================
// Constructor
//=============================================================================
ScribbleVania::ScribbleVania()
{
	eo = new TestPlanetObj();
	background = new TestBackGround();
	player = new Player();
}

//=============================================================================
// Destructor
//=============================================================================
ScribbleVania::~ScribbleVania()
{
    releaseAll();           // call onLostDevice() for every graphics item
	SAFE_DELETE(eo);
	SAFE_DELETE(player);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void ScribbleVania::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	background->Initialize(this);
	eo->Initialize(this);
	player->Initialize(this);
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void ScribbleVania::update()
{
	player->Update(frameTime);
	eo->Update(frameTime);
	background->Update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void ScribbleVania::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void ScribbleVania::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void ScribbleVania::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	background->Draw();
	eo->Draw();
	player->Draw();
	
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ScribbleVania::releaseAll()
{
	player->Shutdown();
	background->Shutdown();
	eo->Shutdown();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void ScribbleVania::resetAll()
{
	background->Reset();
	player->Reset();
	eo->Reset();
    Game::resetAll();
    return;
}
