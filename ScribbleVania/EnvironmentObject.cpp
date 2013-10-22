#include "EnvironmentObject.h"

EnvironmentObject::EnvironmentObject() : GameObject()
{
	_type = ObjectType::EnvironmentObject;
}

EnvironmentObject::EnvironmentObject(unsigned int ID) : GameObject(ID)
{
	_type = ObjectType::EnvironmentObject;
}

EnvironmentObject::~EnvironmentObject()
{
	_game=NULL; 
	this->Shutdown();
}

bool EnvironmentObject::Initialize(Game* game)
{
	return EnvironmentObject::Initialize(game, ZERO_VECTOR);
}

bool EnvironmentObject::Initialize(Game* game, D3DXVECTOR3 position)
{
	_game=game;
	return true;
}

void EnvironmentObject::Shutdown()
{
	objectTexture.onLostDevice();
}


void EnvironmentObject::Draw(COLOR_ARGB color)
{
	objectImage.draw(color);
}

void EnvironmentObject::Draw(SpriteData sd, COLOR_ARGB color)
{
	objectImage.draw(sd,color);
}

void EnvironmentObject::Reset()
{
	objectTexture.onResetDevice();
}

int EnvironmentObject::GetHeight()
{
	return objectImage.getHeight();
}

int EnvironmentObject::GetWidth()
{
	return objectImage.getWidth();
}

D3DXVECTOR3 EnvironmentObject::GetCenter()
{
	D3DXVECTOR3 temp;
	temp.x = objectImage.getCenterX();
	temp.y = objectImage.getCenterY();
	temp.z = this->_position.z;
	return temp;
}