#include "../../../Header/GameObject/EnvironmentObject/TestBackGround.h"

TestBackGround::TestBackGround() : EnvironmentObject()
{
	this->_type = ObjectType::Background;
	_position.z = -1;
	_static=true;
}

TestBackGround::TestBackGround(unsigned int ID) : EnvironmentObject(ID)
{
	this->_type = ObjectType::Background;
	_position.z=-1;
	_static=true;
}

TestBackGround::~TestBackGround()
{
	EnvironmentObject::~EnvironmentObject();
}

bool TestBackGround::Initialize(Game* game)
{
	return TestBackGround::Initialize(game,ZERO_VECTOR);
}


bool TestBackGround::Initialize(Game* game, D3DXVECTOR3 position)
{
	_game=game;
	
	if(!objectTexture.initialize(_game->getGraphics(),TEST_BG))
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



