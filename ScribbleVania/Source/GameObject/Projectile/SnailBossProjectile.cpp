#include "../../../Header/GameObject/Projectile/SnailBossProjectile.h"
#include "../../../Header/ObjectManager.h"
#include "../../../Header/Collidable/BoundingCircle.h"
#include "../../../Header/GameObject/Enemy/RedSnailEnemy.h"

SnailBossProjectile::SnailBossProjectile()
{
}

SnailBossProjectile::SnailBossProjectile(unsigned int id, GameObject* owner) : Projectile(id)
{
	D3DXVECTOR3 direction;
	this->_owner = owner;
	this->_baseSpeed = 300+(rand()%601);
	D3DXVec3Normalize(&direction, &_owner->GetDirection());
	this->_velocity = _baseSpeed*direction;
	_bound = new BoundingCircle(this->_id,this);
	this->_position = owner->GetCenter();
	this->_position.z++;
}

SnailBossProjectile::~SnailBossProjectile()
{
	_owner = NULL;
	_om = NULL;
}

bool SnailBossProjectile::Initialize(ObjectManager* om)
{
	return Initialize(om, ZERO_VECTOR);
}

bool SnailBossProjectile::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!_projectileTexture.initialize(_om->GetGraphics(), SNAIL_BOSS_IMAGE))
	{
		return false;
	}
	else
	{
		if(!_projectileImage.initialize(_om->GetGraphics(),SNAIL_BOSS_WIDTH,SNAIL_BOSS_HEIGHT,SNAIL_BOSS_COLS, &_projectileTexture,0.15f))
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

		if(_velocity.x>0)
		{
			_projectileImage.setFrames(SNAIL_BOSS_SHOT_RIGHT_START,SNAIL_BOSS_SHOT_RIGHT_END);
			_projectileImage.setCurrentFrame(SNAIL_BOSS_SHOT_RIGHT_START);
		}
		else
		{
			_projectileImage.setFrames(SNAIL_BOSS_SHOT_LEFT_START,SNAIL_BOSS_SHOT_LEFT_END);
			_projectileImage.setCurrentFrame(SNAIL_BOSS_SHOT_LEFT_START);
		}

		_projectileImage.setFrameDelay(SNAIL_BOSS_SHOT_ANIMATION_DELAY);
	}


	return true;
}

void SnailBossProjectile::Update(float elapsedTime)
{
	_velocity.y+=(GRAVITY/4)*elapsedTime*elapsedTime;
	Projectile::Update(elapsedTime);
}

void SnailBossProjectile::ProcessCollision(GameObject* obj)
{
	Projectile::ProcessCollision(obj);
	_om->RemoveObject(_id);
	_dying=true;
	if(obj->GetObjectType() ==ObjecType::EnvironmentObject)
	{
		EnvironmentObject* e = (EnvironmentObject*)obj;
		if(e->GetSubType() != EnvSubType::Floor)
			return;
	}
	_om->AddObject(new RedSnailEnemy(_om->GetNextID(),
		_position,(Player*)_om->GetObjectByID(0)));
}

unsigned int SnailBossProjectile::GetOwnerID()
{
	if(_owner==NULL)
	{
		_om->RemoveObject(_id);
		return -1;
	}
	return _owner->GetID();
}