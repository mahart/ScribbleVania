#include "../../../Header/GameObject/EnvironmentObject/TestBarrier.h"
#include "../../../Header/Collidable/BoundingBox.h"

TestBarrier::TestBarrier()
{
	_velocity = ZERO_VECTOR;
	_type = ObjectType::EnvironmentObject;
	_static=true;
	_position.z=1;
	_bound = new BoundingBox(0, this);
}

TestBarrier::TestBarrier(unsigned int ID, unsigned int height, unsigned int width, D3DXVECTOR3 position, ObjectType type)
{
	_velocity = ZERO_VECTOR;
	_id =ID;
	_type = type;
	_static=true;
	_position.z=1;
	_bound = new BoundingBox(ID, this);
	_height = height;
	_width = width;
	_position = position;
}

TestBarrier::~TestBarrier()
{
	SAFE_DELETE(_bound);
	_bound=NULL;
	EnvironmentObject::~EnvironmentObject();
}

bool TestBarrier::Initialize(Game* game)
{
	return TestBarrier::Initialize(game, D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1));
}

bool TestBarrier::Initialize(Game* game, D3DXVECTOR3 position)
{
	_game = game;
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
		//_position = position;
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