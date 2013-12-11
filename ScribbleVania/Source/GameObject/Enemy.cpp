#include "../../Header/GameObject/Enemy.h"

Enemy::Enemy() :GameObject()
{
	_type = ObjectType::Enemy;
	_velocity = ZERO_VECTOR;
}

Enemy::Enemy(unsigned int ID) : GameObject(ID)
{
	_type = ObjectType::Enemy;
	_velocity = ZERO_VECTOR;
}

Enemy::~Enemy()
{
	_om = NULL;
	this->Shutdown();
}

bool Enemy::Initialize(ObjectManager* om)
{
	return Enemy::Initialize(om, ZERO_VECTOR);
}

bool Enemy::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	return true;
}

void Enemy::Shutdown()
{
	objectTexture.onLostDevice();
	if(_bound!=NULL)
		_bound->Shutdown();
}

void Enemy::Reset()
{
	objectTexture.onResetDevice();
	if(_bound!=NULL)
		_bound->Reset();

}

void Enemy::Update(float elapsedTime)
{
	if (_position.y> GAME_HEIGHT)              // if off screen bottom
            _position.y = (float)-objectImage.getHeight();    // position off screen top
	 if (_position.y < -objectImage.getHeight())        // if off screen top
            _position.y = (float)GAME_HEIGHT;          // position off screen bottom
	  if (_position.x < -objectImage.getWidth())         // if off screen left
            _position.x = (float)GAME_WIDTH;           // position off screen right
	  if (_position.x > GAME_WIDTH)               // if off screen right
            _position.x = (float)-objectImage.getWidth();     // position off screen left

	_position += _velocity * elapsedTime;

	objectImage.setX(_position.x);
	objectImage.setY(_position.y);

    objectImage.update(elapsedTime);
	_bound->Update(elapsedTime);
}

void Enemy::Draw(COLOR_ARGB color)
{
	if(!IsDead())
		objectImage.draw(color);
}

void Enemy::Draw(SpriteData sd, COLOR_ARGB color)
{
	if(!IsDead())
		objectImage.draw(sd,color);
}

D3DXVECTOR3 Enemy::GetCenter()
{
	return D3DXVECTOR3(objectImage.getCenterX(),objectImage.getCenterY(),this->_position.z);
}

int Enemy::GetWidth()
{
	return objectImage.getWidth();
}

int Enemy::GetHeight()
{
	return objectImage.getWidth();
}

float Enemy::GetScale()
{
	return objectImage.getScale();
}

D3DXVECTOR3 Enemy::ExitObject(GameObject* obj)
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