#include "../../Header/GameObject/EnvironmentObject.h"

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
	_om=NULL; 
	this->Shutdown();
}

bool EnvironmentObject::Initialize(ObjectManager* om)
{
	return EnvironmentObject::Initialize(om, ZERO_VECTOR);
}

bool EnvironmentObject::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	return true;
}

void EnvironmentObject::Shutdown()
{
	objectTexture.onLostDevice();
	if(_bound!=NULL)
		_bound->Shutdown();
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
	if(_bound!=NULL)
		_bound->Reset();
}

int EnvironmentObject::GetHeight()
{
	return objectImage.getHeight()*objectImage.getScale();
}

int EnvironmentObject::GetWidth()
{
	return objectImage.getWidth()*objectImage.getScale();
}

float EnvironmentObject::GetScale()
{
	return objectImage.getScale();
}

D3DXVECTOR3 EnvironmentObject::GetCenter()
{
	return D3DXVECTOR3(objectImage.getCenterX(),objectImage.getCenterY(),this->_position.z);
}