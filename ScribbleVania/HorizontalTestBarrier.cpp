#include "HorizontalTestBarrier.h"
#include "BoundingBox.h"

HorizontalTestBarrier::HorizontalTestBarrier()
{
	_velocity = ZERO_VECTOR;
	_type = ObjectType::EnvironmentObject;
	_static=true;
	_position.z=1;
	_bound = new BoundingBox(0, this);
}

HorizontalTestBarrier::HorizontalTestBarrier(unsigned int ID, unsigned int height, unsigned int width, D3DXVECTOR3 position)
{
	_velocity = ZERO_VECTOR;
	_id =ID;
	_type = ObjectType::EnvironmentObject;
	_static=true;
	_position.z=1;
	_bound = new BoundingBox(ID, this);
	_height = height;
	_width = width;
	_position = position;
}

HorizontalTestBarrier::~HorizontalTestBarrier()
{
	SAFE_DELETE(_bound);
	_bound=NULL;
	EnvironmentObject::~EnvironmentObject();
}

bool HorizontalTestBarrier::Initialize(Game* game)
{
	return HorizontalTestBarrier::Initialize(game, D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1));
}

bool HorizontalTestBarrier::Initialize(Game* game, D3DXVECTOR3 position)
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

void HorizontalTestBarrier::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
	_bound->Update(elapsedTime);
}

void HorizontalTestBarrier::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	//EnvironmentObject::Draw(color);
}



void HorizontalTestBarrier::Draw(SpriteData sd, COLOR_ARGB color)
{
	_bound->Draw(sd,color);
	//EnvironmentObject::Draw(sd,color);
}