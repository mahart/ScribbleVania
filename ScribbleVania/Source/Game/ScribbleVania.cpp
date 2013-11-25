#include "../../Header/Game/ScribbleVania.h"
#include "../../Header/GameObject/GameObject.h"
#include "../../Header/GameObject/EnvironmentObject/TestPlanetObj.h"
#include "../../Header/GameObject/EnvironmentObject/TestBackground.h"
//#include "Room.h"
#include "../../Header/ObjectManager.h"

//=============================================================================
// Constructor
//=============================================================================
ScribbleVania::ScribbleVania()
{
	_manager = new ObjectManager(this);
}

//=============================================================================
// Destructor
//=============================================================================
ScribbleVania::~ScribbleVania()
{
    releaseAll();           // call onLostDevice() for every graphics item
	SAFE_DELETE(_manager);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void ScribbleVania::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	_manager->Initialize();
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void ScribbleVania::update()
{
	_manager->Update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void ScribbleVania::ai()
{
	_manager->AI();
}

//=============================================================================
// Handle collisions
//=============================================================================
void ScribbleVania::collisions()
{
	_manager->Collision();
}

//=============================================================================
// Render game items
//=============================================================================
void ScribbleVania::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	_manager->Draw();
	/*background->Draw();
	eo->Draw();
	player->Draw();
	*/
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void ScribbleVania::releaseAll()
{
	_manager->ShutDown();
	/*player->Shutdown();
	background->Shutdown();
	eo->Shutdown();*/
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void ScribbleVania::resetAll()
{
	_manager->Reset();
	/*background->Reset();
	player->Reset();
	eo->Reset();*/
    Game::resetAll();
    return;
}
