#include "TestBackGround.h"

TestBackGround::TestBackGround() : EnvironmentObject()
{
	_static=true;
}

TestBackGround::TestBackGround(unsigned int ID) : EnvironmentObject(ID)
{
	_static=true;
}

TestBackGround::~TestBackGround()
{
	EnvironmentObject::~EnvironmentObject();
}

bool TestBackGround::Initialize(Game* game)
{
	_game=game;
	
	if(!objectTexture.initialize(_game->getGraphics(),NEBULA_IMAGE))
	{
		return false;
	}
	else
	{
		if(! objectImage.initialize(_game->getGraphics(),0, 0,0,&objectTexture))
		{
			return false;
		}
		_position.x = 0;
		_position.y = 0;
	}
	return true;
}

void TestBackGround::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
}



