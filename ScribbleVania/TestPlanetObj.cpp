#include "TestPlanetObj.h"

TestPlanetObj::TestPlanetObj() : EnvironmentObject()
{
	_static=true;
}

TestPlanetObj::TestPlanetObj(unsigned int ID) : EnvironmentObject(ID)
{
	_static=true;
}

TestPlanetObj::~TestPlanetObj()
{
	EnvironmentObject::~EnvironmentObject();
}

bool TestPlanetObj::Initialize(Game* game)
{
	_game=game;
	
	if(!objectTexture.initialize(_game->getGraphics(),PLANET_IMAGE))
	{
		return false;
	}
	else
	{
		if(! objectImage.initialize(_game->getGraphics(),0, 0,0,&objectTexture))
		{
			return false;
		}
		_position.x = GAME_WIDTH*0.5f - objectImage.getWidth() *0.5f;
		_position.y = GAME_HEIGHT*0.5f - objectImage.getHeight()*0.5f;
	}
	return true;
}

void TestPlanetObj::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
}