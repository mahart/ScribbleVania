#include "../../../Header/GameObject/Boss/SnailBoss.h"
#include "../../../Header/Collidable/BoundingBox.h"
#include "../../../Header/GameObject/Projectile/SnailBossProjectile.h"

SnailBoss::SnailBoss() : Boss()
{
	_bossType = BossType::Snail;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY;
	_dir = Direction::Left;
	_bounceCount=0;
	_bounceTimer=0.0f;
	_attackTimer = 0.0f;
	_startBounceTime=10.0f;
	_bounceCountStop=4;
	_hitPoints = SNAIL_BOSS_HP;
	_hitThreshold = FROG_BOSS_THRESHOLD;
	_hitCount=0;
}

SnailBoss::SnailBoss(unsigned int ID, Player* p, D3DXVECTOR3 position):Boss(ID)
{
	_bossType = BossType::Snail;
	_bound = new BoundingBox(ID, this);

	_position = ZERO_VECTOR;
	_fallAccel= GRAVITY;
	_dir = Direction::Left;
	_position=position;
	_state = SnailBossState::Falling;
	_player = p;
	_bounceCount=0;
	_bounceTimer=0.0f;
	_attackTimer=0.0f;
	_startBounceTime=10.0f;
	_bounceCountStop=4;
	srand(ID);
	_hitPoints = SNAIL_BOSS_HP;
	_hitThreshold = FROG_BOSS_THRESHOLD;
	_hitCount=0;
}

SnailBoss::~SnailBoss()
{
	Boss::~Boss();

	_player=NULL;
}

bool SnailBoss::Initialize(ObjectManager* om)
{
	return SnailBoss::Initialize(om,D3DXVECTOR3(75,GAME_HEIGHT/2, 3));
}

bool SnailBoss::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om = om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!_bossTexture.initialize(_om->GetGraphics(),SNAIL_BOSS_IMAGE))
	{
		return false;
	}
	else
	{
		if(!_bossImage.initialize(_om->GetGraphics(),SNAIL_BOSS_WIDTH,SNAIL_BOSS_HEIGHT,SNAIL_BOSS_COLS, &_bossTexture,5.0f))
		{
			return false;
		}

		if(!_bound->Initialize(_om,_bossImage.getHeight()*_bossImage.getScale()-20, _bossImage.getWidth() * _bossImage.getScale()-30))
		{
			return false;
		}
	}

	_bossImage.setFrames(SNAIL_BOSS_START_FRAME, SNAIL_BOSS_END_FRAME);
	_bossImage.setCurrentFrame(SNAIL_BOSS_START_FRAME);
	_bossImage.setFrameDelay(SNAIL_BOSS_ANIMATION_DELAY);
	_om->SnailDead(_state==SnailBossState::Dead);
	return true;
}

void SnailBoss::Draw(COLOR_ARGB color)
{
	if(_state != SnailBossState::Dead)
		Boss::Draw(color);
}

void SnailBoss::Draw(SpriteData sd, COLOR_ARGB color)
{
	if(_state != SnailBossState::Dead)
		Boss::Draw(color);
}

void SnailBoss::Update(float elapsedTime)
{
	switch(_state)
	{
		case SnailBossState::Falling:
			UpdateFalling(elapsedTime);
			break;
		case SnailBossState::Bouncing:
			UpdateBouncing(elapsedTime);
			break;
		case SnailBossState::Attack:
			UpdateAttacking(elapsedTime);
			break;
		case SnailBossState::Dead:
			return;
		default:
			break;
	}
	Boss::Update(elapsedTime);
}

void SnailBoss::UpdateBouncing(float elapsedTime)
{
	if(_bounceCount>=_bounceCountStop)
	{
		_bounceCount=0;
		_bounceCountStop = 4 +(rand()%7);
		_state = SnailBossState::Falling;
	}
}

void SnailBoss::UpdateFalling(float elaspedTime)
{
	_velocity.y+=_fallAccel*elaspedTime*elaspedTime;
}

void SnailBoss::UpdateAttacking(float elapsedTime)
{
	_bounceTimer+=elapsedTime;
	_attackTimer+=elapsedTime;

	if(_bounceTimer>=_startBounceTime)
	{
		_bounceTimer=0;
		_startBounceTime=5+(rand()%11);
		float vel = (rand()%501);
		_state=SnailBossState::Bouncing;
		_velocity.y=-500.0f-vel;
		if(_position.x<_player->GetPosition().x)
		{
			_velocity.x=500.0f+vel;
		}
		else
		{
			_velocity.x=-500.0f-vel;
		}
		SwitchBouncing();
	}
	else if(_attackTimer >= 3.0f)
	{
		_attackTimer=0;
		_om->AddObject(new SnailBossProjectile(_om->GetNextID(), this));
	}

}

void SnailBoss::ProcessCollision(GameObject* obj)
{
	if((obj->GetObjectType() == ObjectType::EnvironmentObject))
		ExitObject(obj);
	
	if(_state == SnailBossState::Dead)
		return;

	switch(obj->GetObjectType())
	{
		case ObjectType::EnvironmentObject:
			EnvironmentCollision((EnvironmentObject*)obj);
			break;
		case ObjectType::Player:
			PlayerCollision((Player*)obj);
			break;
		case ObjectType::Projectile:
			_hitPoints--;
			break;
		default:
			break;
	}
}

void SnailBoss::PlayerCollision(Player* obj)
{
	D3DXVECTOR3 distance, speed;
	if(obj->GetCenter().x < GetCenter().x)
	{
		distance = D3DXVECTOR3(((BoundingBox*)_bound)->Left()-(obj->GetPosition().x+obj->GetWidth())-1,-1,0);
		speed = D3DXVECTOR3(-250,-100,0);
	}
	else
	{
		distance = D3DXVECTOR3(((BoundingBox*)_bound)->Right() - obj->GetPosition().x +1,-1,0);
		speed = D3DXVECTOR3(250,-100,0);
	}

	obj->DBounce(distance);
	obj->VBounce(speed);
}

void SnailBoss::EnvironmentCollision(EnvironmentObject* obj)
{
	switch(obj->GetSubType())
	{
		case EnvSubType::Floor:
			FloorCollision(obj);
			break;
		case EnvSubType::Door:
		case EnvSubType::Ledge:
		case EnvSubType::Wall:
			WallCollision(obj);
			break;
		default:
			break;
	}
}

void SnailBoss::FloorCollision(EnvironmentObject* obj)
{
	if(_state==SnailBossState::Falling && _position.y < obj->GetPosition().y)
	{
		_velocity=ZERO_VECTOR;
		SwitchStanding();
		_state=SnailBossState::Attack;
	}
	else if(_state == SnailBossState::Bouncing)
	{
		_velocity.y*=-1.0f;
		_bounceCount++;
	}
	else
	{
		_velocity.y=0;
	}
}

void SnailBoss::WallCollision(EnvironmentObject* obj)
{
	if(_state==SnailBossState::Bouncing)
	{
		_velocity.x*=-1.0f;
		_bounceCount++;
	}
	else
	{
		_velocity.x=0;
	}
}

D3DXVECTOR3 SnailBoss::GetDirection()
{
	if(_player->GetPosition().x>_position.x)
		return D3DXVECTOR3(1,-1,0);
	else
		return D3DXVECTOR3(-1,-1,0);
}

void SnailBoss::SwitchBouncing()
{
	if(_position.x < _player->GetPosition().x)
	{
		_bossImage.setFrames(SNAIL_BOSS_START_FRAME_BOUNCING_RIGHT, SNAIL_BOSS_END_FRAME_BOUNCING_RIGHT);
		_bossImage.setCurrentFrame(SNAIL_BOSS_START_FRAME_BOUNCING_RIGHT);
	}
	else
	{
		_bossImage.setFrames(SNAIL_BOSS_START_FRAME_BOUNCING_LEFT, SNAIL_BOSS_END_FRAME_BOUNCING_LEFT);
		_bossImage.setCurrentFrame(SNAIL_BOSS_START_FRAME_BOUNCING_LEFT);
	}
}

void SnailBoss::SwitchStanding()
{
	if(_position.x < _player->GetPosition().x)
	{
		_bossImage.setFrames(SNAIL_BOSS_START_FRAME_STANDING_RIGHT, SNAIL_BOSS_END_FRAME_STANDING_RIGHT);
		_bossImage.setCurrentFrame(SNAIL_BOSS_START_FRAME_STANDING_RIGHT);
	}
	else
	{
		_bossImage.setFrames(SNAIL_BOSS_START_FRAME_STANDING_LEFT, SNAIL_BOSS_END_FRAME_STANDING_LEFT);
		_bossImage.setCurrentFrame(SNAIL_BOSS_START_FRAME_STANDING_LEFT);
	}
}

void SnailBoss::AI()
{
	if(_state==SnailBossState::Dead)
		return;

	if(_hitPoints<=0)
	{
		_state = SnailBossState::Dead;
		_om->SnailDead(true);
	}

	
}

