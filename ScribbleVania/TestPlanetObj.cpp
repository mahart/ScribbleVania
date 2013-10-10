#include "TestPlanetObj.h"
#include "BoundingCircle.h"

TestPlanetObj::TestPlanetObj() : EnvironmentObject()
{
	_static=true;
	_bound = new BoundingCircle(0, this);
}

TestPlanetObj::TestPlanetObj(unsigned int ID) : EnvironmentObject(ID)
{
	_static=true;
	_bound = new BoundingCircle(ID, this);
}

TestPlanetObj::~TestPlanetObj()
{
	SAFE_DELETE(_bound);
	_bound=NULL;
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
		int rad=0;
		if(this->GetWidth()>this->GetHeight())
		{
			rad = this->GetWidth()/2;
		}
		else
		{
			rad = this ->GetHeight()/2;
		}

		if(!_bound->Initialize(_game,rad,-1))
		{
			return false;
		}
	}
	return true;
}

void TestPlanetObj::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
	_bound->Update(elapsedTime);
}

void TestPlanetObj::Draw(SpriteData sd, COLOR_ARGB color)
{
	_bound->Draw(sd,color);
	EnvironmentObject::Draw(sd,color);
}

void TestPlanetObj::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	EnvironmentObject::Draw(color);
}