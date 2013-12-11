#include "../../../Header/GameObject/Projectile/BoringProjectile.h"
#include "../../../Header/ObjectManager.h"
#include "../../../Header/Collidable/BoundingCircle.h"

BoringProjectile::BoringProjectile() : Projectile()
{
}

BoringProjectile::BoringProjectile(unsigned int id, GameObject* owner) : Projectile(id)
{
	D3DXVECTOR3 direction;
	this->_owner = owner;
	this->_baseSpeed = BORING_P_BASE_SPEED;
	D3DXVec3Normalize(&direction, &_owner->GetDirection());
	this->_velocity = _baseSpeed*direction;
	_bound = new BoundingCircle(this->_id,this);
	this->_position.x = owner->GetCenter().x;
	this->_position.y = owner->GetCenter().y;
	this->_position.z = owner->GetPosition().z+1;
}

BoringProjectile::~BoringProjectile()
{
	_owner = NULL;
	_om = NULL;
}

bool BoringProjectile::Initialize(ObjectManager* om)
{
	return Initialize(om, ZERO_VECTOR);
}

bool BoringProjectile::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!_projectileTexture.initialize(_om->GetGraphics(), BASIC_SHOT_IMAGE))
	{
		return false;
	}
	else
	{
		if(!_projectileImage.initialize(_om->GetGraphics(), 64, 64, 1, &_projectileTexture,0.15f))
		{
			return false;
		}
		int rad=0;
		if(this->GetWidth()>this->GetHeight())
		{
			rad = this->GetWidth()/2;
		}
		else
		{
			rad = this ->GetHeight()/2;
		}
		rad = rad * _projectileImage.getScale();
		if(!_bound->Initialize(_om, rad, -1))
		{
			return false;
		}
	}
	return true;
}



void BoringProjectile::ProcessCollision(GameObject* obj)
{
	Projectile::ProcessCollision(obj);
	_dying=true;
	_om->RemoveObject(_id);
}

unsigned int BoringProjectile::GetOwnerID()
{
	if(_owner==NULL)
	{
		_om->RemoveObject(_id);
		return -1;
	}
	return _owner->GetID();
}