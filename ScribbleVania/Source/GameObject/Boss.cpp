#include "../../Header/GameObject/Boss.h"


Boss::Boss()
{
	_type = ObjectType::Boss;
	_velocity = ZERO_VECTOR;
}

Boss::Boss(unsigned int ID):GameObject(ID)
{
	_type = ObjectType::Boss;
	_velocity = ZERO_VECTOR;
}

Boss::~Boss()
{
	GameObject::~GameObject();
	_om=NULL;
	this->Shutdown();
}

void Boss::Shutdown()
{
	_bossTexture.onLostDevice();
	if(_bound!=NULL)
		_bound->Shutdown();
}

void Boss::Reset()
{
	_bossTexture.onResetDevice();
	if(_bound!=NULL)
		_bound->Reset();
}

void Boss::Update(float elapsedTime)
{
	if (_position.y> GAME_HEIGHT)              // if off screen bottom
		_position.y = (float)-_bossImage.getHeight();    // position off screen top
	if (_position.y < -_bossImage.getHeight())        // if off screen top
	    _position.y = (float)GAME_HEIGHT;          // position off screen bottom
	if (_position.x < -_bossImage.getWidth())         // if off screen left
		_position.x = (float)GAME_WIDTH;           // position off screen right
	if (_position.x > GAME_WIDTH)               // if off screen right
        _position.x = (float)-_bossImage.getWidth();     // position off screen left
	
	_position+=_velocity*elapsedTime;

	_bossImage.setX(_position.x);
	_bossImage.setY(_position.y);

	_bossImage.update(elapsedTime);
	_bound->Update(elapsedTime);
}

void Boss::Draw(COLOR_ARGB color)
{
	_bossImage.draw(color);
}

void Boss::Draw(SpriteData sd, COLOR_ARGB color)
{
	_bossImage.draw(sd,color);
}

D3DXVECTOR3 Boss::GetCenter()
{
	return D3DXVECTOR3(_bossImage.getCenterX(), _bossImage.getCenterY(),_position.z);
}

int Boss::GetWidth()
{
	return _bossImage.getWidth();
}

int Boss::GetHeight()
{
	return _bossImage.getWidth();
}

float Boss::GetScale()
{
	return _bossImage.getScale();
}

D3DXVECTOR3 Boss::ExitObject(GameObject* obj)
{
	D3DXVECTOR3 diff = GetCenter()-obj->GetCollidable()->GetNearestPoint(GetCenter());
	diff.z=0;

	D3DXVECTOR3 direction;
	if(diff.x==0 && diff.y==0)
	{
		D3DXVECTOR3 temp(_velocity.x *-1, _velocity.y *-1,0);
		D3DXVec3Normalize(&direction, &temp);
	}
	else
	{
		D3DXVec3Normalize(&direction,&diff);
	}

	while(_bound->Intersects(obj->GetCollidable()))
	{
		_position+=direction*0.1f;
	}

	return direction;
}