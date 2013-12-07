#include "../../Header/GameObject/Projectile.h"


Projectile::Projectile()
{
	_type=ObjectType::Projectile;
}

Projectile::Projectile(unsigned int id) : GameObject(id)
{
	_type=ObjectType::Projectile;
}

Projectile::~Projectile()
{
	_om = NULL;
	Shutdown();
}

void Projectile::Update(float elapsedTime)
{
	if (_position.y> GAME_HEIGHT)              // if off screen bottom
		_position.y = (float)-_projectileImage.getHeight();    // position off screen top
	if (_position.y < -_projectileImage.getHeight())        // if off screen top
        _position.y = (float)GAME_HEIGHT;          // position off screen bottom
	if (_position.x < -_projectileImage.getWidth())         // if off screen left
        _position.x = (float)GAME_WIDTH;           // position off screen right
	if (_position.x > GAME_WIDTH)               // if off screen right
        _position.x = (float)-_projectileImage.getWidth();     // position off screen left
	
	_position += _velocity * elapsedTime;

	_projectileImage.update(elapsedTime);
	_bound->Update(elapsedTime);

	_projectileImage.setX(_position.x);
	_projectileImage.setY(_position.y);
}

void Projectile::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	_projectileImage.draw(color);
	
}

void Projectile::Draw(SpriteData sd, COLOR_ARGB color)
{
	_projectileImage.draw(sd,color);
}


bool Projectile::Initialize(ObjectManager* om)
{
	return Projectile::Initialize(om, _owner->GetCenter());
}

bool Projectile::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	return false;
}

void Projectile::Shutdown()
{
	_projectileTexture.onLostDevice();
}

void Projectile::Reset()
{
	_projectileTexture.onResetDevice();
	if(_bound!=NULL)
		_bound->Reset();
}
		
//Getters
D3DXVECTOR3 Projectile::GetCenter()
{
	return D3DXVECTOR3(_projectileImage.getCenterX(),_projectileImage.getCenterY(),_position.z);
}

int Projectile::GetWidth()
{
	return _projectileImage.getWidth();
}

int Projectile::GetHeight()
{
	return _projectileImage.getHeight();
}

float Projectile::GetScale()
{
	return _projectileImage.getScale();
}

void Projectile::ProcessCollision(GameObject* obj)
{
	if(obj->GetObjectType()==ObjectType::Player)
		return;

	D3DXVECTOR3 diff = GetCenter() - obj->GetCollidable()->GetNearestPoint(GetCenter());
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
		_bound->Update(0);
	}

}