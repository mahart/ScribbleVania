#include "../../../Header/GameObject/EnvironmentObject/TestBarrier.h"
#include "../../../Header/Collidable/BoundingBox.h"

TestBarrier::TestBarrier():EnvironmentObject()
{
	_velocity = ZERO_VECTOR;
	_subType = EnvSubType::Other;
	_static=true;
	_bound = new BoundingBox(0, this);
}

TestBarrier::TestBarrier(unsigned int ID, unsigned int height, unsigned int width, D3DXVECTOR3 position, EnvSubType type) : EnvironmentObject(ID)
{
	_velocity = ZERO_VECTOR;
	_subType = type;
	_static=true;
	
	_bound = new BoundingBox(ID, this);
	_height = height;
	_width = width;
	_position = position;

}

TestBarrier::~TestBarrier()
{
	EnvironmentObject::~EnvironmentObject();
	SAFE_DELETE(_bound);
	_bound=NULL;
}

bool TestBarrier::Initialize(Game* game)
{
	return TestBarrier::Initialize(game, D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1));
}

bool TestBarrier::Initialize(Game* game, D3DXVECTOR3 position)
{
	_game = game;
	if(_position == ZERO_VECTOR)
			_position = position;
	//BOX_IMAGE
	if(!objectTexture.initialize(_game->getGraphics(), BOX_IMAGE))
	{
		return false;
	}
	else
	{
		if(!objectImage.initialize(_game->getGraphics(), _height, _width,0,&objectTexture))
		{
			return false;
		}
		
		if(!_bound->Initialize(_game, objectImage.getWidth(), objectImage.getHeight()))
		{
			return false;
		}
	}
	return true;
}

void TestBarrier::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
	_bound->Update(elapsedTime);
}

void TestBarrier::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	//EnvironmentObject::Draw(color);
}



void TestBarrier::Draw(SpriteData sd, COLOR_ARGB color)
{
	_bound->Draw(sd,color);
	//EnvironmentObject::Draw(sd,color);
}