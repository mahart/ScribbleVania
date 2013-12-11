#include "../../../Header/GameObject/Boss/FrogBoss.h"
#include "../../../Header/Collidable/BoundingBox.h"
#include "../../../Header/GameObject/Enemy/BombFrogEnemy.h"
#include "../../../Header/GameObject/Enemy/FatFrogEnemy.h"

FrogBoss::FrogBoss():Boss()
{
	_bossType = BossType::Frog;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY;
	_dir = Direction::Left;
	_state=FrogBossState::Fall;
	_wasHit=false;
	_switchToGlide=false;
	_jumpCount=0;
	_maxJumpCount=2;
	_glideShotTime=1.0f;
	_glideShotTimer=0;
	_hitPoints = FROG_BOSS_HP;
	_hitThreshold = FROG_BOSS_THRESHOLD;
	_hitCount=0;
}

FrogBoss::FrogBoss(unsigned int ID, Player* p,D3DXVECTOR3 position) : Boss(ID)
{
	_bossType = BossType::Frog;
	_position=position;
	_player =p;
	_bound = new BoundingBox(ID,this);
	_fallAccel = GRAVITY;
	_dir = Direction::Left;
	_state=FrogBossState::Fall;
	_wasHit=false;
	_switchToGlide=false;
	_jumpCount=0;
	_maxJumpCount=2;
	_glideShotTime=1.0f;
	_glideShotTimer=0;
	_hitPoints = FROG_BOSS_HP;
	_hitThreshold = FROG_BOSS_THRESHOLD;
	_hitCount=0;
}

FrogBoss::~FrogBoss()
{
	Boss::~Boss();
	_player = NULL;
}

bool FrogBoss::Initialize(ObjectManager* om)
{
	return FrogBoss::Initialize(om, ZERO_VECTOR);
}

bool FrogBoss::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!_bossTexture.initialize(_om->GetGraphics(), FAT_FROG_IMAGE))
	{
		return false;
	}
	else
	{
		if(!_bossImage.initialize(_om->GetGraphics(), FAT_FROG_WIDTH, FAT_FROG_HEIGHT, FAT_FROG_COLS, &_bossTexture, 2.0f))
		{
			return false;
		}
		
		if(!_bound->Initialize(_om,  (_bossImage.getHeight()-30)*_bossImage.getScale(),_bossImage.getWidth() * _bossImage.getScale()))
		{
			return false;
		}
	}

	_bossImage.setFrames(FAT_FROG_START_FRAME,FAT_FROG_END_FRAME);
	_bossImage.setCurrentFrame(FAT_FROG_START_FRAME);
	_bossImage.setFrameDelay(FAT_FROG_ANIMATION_DELAY);
	return true;
}

void FrogBoss::Draw(COLOR_ARGB color)
{
	if(_state!=FrogBossState::Dead)
		Boss::Draw(color);
}

void FrogBoss::Draw(SpriteData sd, COLOR_ARGB color)
{
	if(_state!=FrogBossState::Dead)
		Boss::Draw(sd,color);
}

void FrogBoss::Update(float elapsedTime)
{
	if(_state==FrogBossState::Dead)
		return;

	switch(_state)
	{
		case FrogBossState::Patrol:
			UpdatePatrol(elapsedTime);
			break;
		case FrogBossState::Jump:
			UpdateJump(elapsedTime);
			break;
		case FrogBossState::Glide:
			UpdateGlide(elapsedTime);
			break;
		case FrogBossState::Fall:
			UpdateFall(elapsedTime);
			break;
		default:
			break;
	}

	Boss::Update(elapsedTime);
}

void FrogBoss::UpdateFall(float elapsedTime)
{
	_velocity.y += _fallAccel*elapsedTime*elapsedTime;
}

void FrogBoss::UpdateJump(float elapsedTime)
{
	_velocity.y += _fallAccel*elapsedTime*elapsedTime;

	if(_velocity.y>=0)
	{
		if(_jumpCount<=_maxJumpCount)
			Jump();
		else if(_switchToGlide)
			_state=FrogBossState::Glide;
	}
}

void FrogBoss::UpdateGlide(float elapsedTime)
{
	_velocity.y +=( _fallAccel/500)*elapsedTime*elapsedTime;
	_glideShotTimer+=elapsedTime;
	if(_glideShotTimer>=_glideShotTime)
	{
		_glideShotTimer=0;
		_om->AddObject(new BombFrogEnemy(_om->GetNextID(), GetCenter(),_player));
	}
}

void FrogBoss::UpdatePatrol(float elapsedTime)
{
	if(_bossImage.getCurrentFrame()==3)
	{
		Jump();
		_state = FrogBossState::Jump;
	}
}

void FrogBoss::ProcessCollision(GameObject* obj)
{
	if(_state == FrogBossState::Dead)
		return;


	if(obj->GetObjectType() == ObjectType::Player)
	{
		if(obj->GetPosition().y<((BoundingBox*)_bound)->Bottom())
			((Player*)obj)->ExitObject(this);
		else
			ExitObject(obj);
	}
	else if(obj->GetObjectType()!=ObjectType::Projectile)
		ExitObject(obj);
	
	switch(obj->GetObjectType())
	{
		case ObjectType::EnvironmentObject:
			EnvironmentCollision((EnvironmentObject*)obj);
			break;
		case ObjectType::Player:
			PlayerCollision((Player*) obj);
			break;
		case ObjectType::Projectile:
			ProjectileCollision((Projectile*)obj);
			break;
		default:
			DefaultCollision(obj);
			break;
	}
}

void FrogBoss::EnvironmentCollision(EnvironmentObject* obj)
{
	switch(obj->GetSubType())
	{
		case EnvSubType::Floor:
			FloorCollision(obj);
			break;
		case EnvSubType::Ledge:
		case EnvSubType::Door:
		case EnvSubType::Wall:
			WallCollision(obj);
			break;
		default:
			DefaultCollision(obj);
			break;
	}
}

void FrogBoss::FloorCollision(EnvironmentObject* obj)
{
	//hit ceiling
	if(obj->GetPosition().y<_position.y)
	{
		_velocity.y=0;
		return;
	}

	if(_state==FrogBossState::Jump 
		|| _state==FrogBossState::Fall 
		||_state== FrogBossState::Glide)
	{
		if(_state==FrogBossState::Glide)
		{
			_switchToGlide = false;
			_hitCount=0;
		}
		_velocity=ZERO_VECTOR;
		_state= FrogBossState::Patrol;
		_jumpCount=0;
	}
}

void FrogBoss::WallCollision(EnvironmentObject* obj)
{
	if(_state==FrogBossState::Jump 
		|| _state==FrogBossState::Fall)
	{
		_velocity = ZERO_VECTOR;
		_state=FrogBossState::Patrol;
		_jumpCount=1;
	}
	else if(_state == FrogBossState::Glide)
		_velocity.x*=-1;
}

void FrogBoss::PlayerCollision(Player* obj)
{
	//Damage Player

	//Slide player out of frog

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

void FrogBoss::ProjectileCollision(Projectile* obj)
{
	_hitCount++;
	_hitPoints--;
	if(_state==FrogBossState::Patrol)
	{
		_state= FrogBossState::Fall;
	}
		_wasHit=true;
}

void FrogBoss::DefaultCollision(GameObject* obj)
{
}

void FrogBoss::AI()
{
	if(_hitCount>=_hitThreshold)
		_switchToGlide=true;

	if(_hitPoints<=0)
		_state = FrogBossState::Dead;

	D3DXVECTOR3 ppos = _player->GetPosition();
	if(ppos.x < _position.x)
		_dir = Direction::Left;
	else
		_dir = Direction::Right;

	if(ppos.x>((BoundingBox*)_bound)->Left() 
		&& ppos.x<((BoundingBox*)_bound)->Right() 
		&& ppos.y > _position.y && _state == FrogBossState::Jump
		&&!_switchToGlide)
	{
		_velocity.x = 0;
		_velocity.y = 100;
		_state = FrogBossState::Fall;
		//frame = attack?
	}

}

void FrogBoss::Jump()
{
	_jumpCount++;
	_velocity.y = -1000;

	if(_dir==Direction::Left)
	{
		_velocity.x = -200;
	}
	else
	{
		_velocity.x = 200;
	}
}