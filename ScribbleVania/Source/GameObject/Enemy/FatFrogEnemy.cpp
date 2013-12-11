#include "../../../Header/GameObject/Enemy/FatFrogEnemy.h"
#include "../../../Header/Collidable/BoundingBox.h"

FatFrogEnemy::FatFrogEnemy() : Enemy()
{
	_enemyType = EnemyType::FatFrog;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY;
	_dir = Direction::Right;
	_state = FatFrogState::Falling;
	_jumpTimer=0;
	_jumpTime =2.0f;
	_hitPoints = FAT_FROG_HP;
}

FatFrogEnemy::FatFrogEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p) : Enemy(ID)
{
	_enemyType = EnemyType::FatFrog;
	_bound = new BoundingBox(ID,this);
	_position=position;
	_fallAccel = GRAVITY;

	_dir = Direction::Right;
	_state = FatFrogState::Falling;
	_player=p;
	_jumpTimer=0;
	_jumpTime = 2.0f;
	_hitPoints = FAT_FROG_HP;
}

FatFrogEnemy::~FatFrogEnemy()
{
	Enemy::~Enemy();
	_player = NULL;
}

bool FatFrogEnemy::Initialize(ObjectManager* om)
{
	return FatFrogEnemy::Initialize(om,ZERO_VECTOR);
}

bool FatFrogEnemy::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!objectTexture.initialize(_om->GetGraphics(), FAT_FROG_IMAGE))
	{
		return false;
	}
	else
	{
		if(!objectImage.initialize(_om->GetGraphics(), FAT_FROG_WIDTH, FAT_FROG_HEIGHT, FAT_FROG_COLS, &objectTexture, 0.5f))
		{
			return false;
		}
		
		if(!_bound->Initialize(_om,  (objectImage.getHeight()-30)*objectImage.getScale(),objectImage.getWidth() * objectImage.getScale()))
		{
			return false;
		}
	}

	objectImage.setFrames(FAT_FROG_START_FRAME,FAT_FROG_END_FRAME);
	objectImage.setCurrentFrame(FAT_FROG_START_FRAME);
	objectImage.setFrameDelay(FAT_FROG_ANIMATION_DELAY);

	if(_state==FatFrogState::Dead)
	{
		_hitPoints = FAT_FROG_HP;
		_state = FatFrogState::Falling;
	}
	return true;
}

void FatFrogEnemy::Draw(COLOR_ARGB color)
{
	if(_state!=FatFrogState::Dead)
		Enemy::Draw(color);
}

void FatFrogEnemy::Draw(SpriteData sd, COLOR_ARGB color)
{
	if(_state!=FatFrogState::Dead)
		Enemy::Draw(sd, color);
}

void FatFrogEnemy::Update(float elapsedTime)
{
	if(_state==FatFrogState::Dead)
		return;

	if(_state == FatFrogState::Falling || _state==FatFrogState::Jumping)
		_velocity.y+=_fallAccel*elapsedTime*elapsedTime;
	

	if(_state==FatFrogState::Patrolling)
	{
		_jumpTimer+=elapsedTime;
		if(_jumpTimer>=_jumpTime)
		{
			_jumpTimer=0;
			_jumpTime= 2+(rand()%4)-1;
			_state=FatFrogState::Jumping;
			_velocity.y=-1000;

			
	//TEMP ANIMATION
			if(_dir==Direction::Left)
			{
				objectImage.flipHorizontal(false);
			}
			else
			{
				objectImage.flipHorizontal(true);
			}

			if(_dir==Direction::Left)
			{
				_velocity.x=-500;
			}
			else
			{
				_velocity.x=500;
			}
		}
	}

	Enemy::Update(elapsedTime);
}

void FatFrogEnemy::ProcessCollision(GameObject* obj)
{
	if(obj->GetObjectType() == ObjectType::Player)
	{
		if(obj->GetPosition().y<((BoundingBox*)_bound)->Bottom())
			((Player*)obj)->ExitObject(this);
		else
			ExitObject(obj);
	}
	else if(obj->GetObjectType()!=ObjectType::Projectile)
		ExitObject(obj);
	else
	{
		_hitPoints--;
		if(_hitPoints<=0)
		{
			_state = FatFrogState::Dead;
			return;
		}
	}

	if(_state == FatFrogState::Dead)
		return;

	switch(obj->GetObjectType())
	{
		case ObjecType::EnvironmentObject:
			EnvironmentCollision((EnvironmentObject*) obj);
			break;
		case ObjectType::Player:
			PlayerCollision((Player*)obj);
			break;
		default:
			DefaultCollision(obj);
			break;
	}
}

void FatFrogEnemy::EnvironmentCollision(EnvironmentObject* obj)
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

void FatFrogEnemy::DefaultCollision(GameObject* obj)
{
}

void FatFrogEnemy::FloorCollision(EnvironmentObject* obj)
{
	//hit ceiling
	if(obj->GetPosition().y<_position.y)
	{
		_velocity.y=0;
		return;
	}

	if(_state==FatFrogState::Jumping || _state==FatFrogState::Falling)
	{
		_velocity=ZERO_VECTOR;
		_state= FatFrogState::Patrolling;
	}
}

void FatFrogEnemy::WallCollision(EnvironmentObject* obj)
{
	if(_state==FatFrogState::Jumping || _state==FatFrogState::Falling)
	{
		_velocity =ZERO_VECTOR;
		_state = FatFrogState::Patrolling;
	}
}

void FatFrogEnemy::PlayerCollision(Player* obj)
{
	//damage player;

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

void FatFrogEnemy::AI()
{
	if(_state == FatFrogState::Dead)
		return;

	D3DXVECTOR3 ppos = _player->GetPosition();
	if(ppos.x < _position.x)
		_dir = Direction::Left;
	else
		_dir = Direction::Right;

	if(ppos.x>((BoundingBox*)_bound)->Left() 
		&& ppos.x<((BoundingBox*)_bound)->Right() 
		&& ppos.y > _position.y && _state == FatFrogState::Jumping)
	{
		_velocity.x = 0;
		_velocity.y = 100;
		_state = FatFrogState::Falling;
		//frame = attack?
	}
}