#include "../../../Header/GameObject/Enemy/BombFrogEnemy.h"

BombFrogEnemy::BombFrogEnemy() : Enemy()
{
	_enemyType = EnemyType::BombFrog;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY/10;
	_dir = Direction::Right;
	_state = FatFrogState::Falling;
	_jumpTimer=0;
	_jumpTime =2.0f;
	_jumpCount=0;
	_maxJumps=2;
}

BombFrogEnemy::BombFrogEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p) : Enemy(ID)
{
	_enemyType = EnemyType::BombFrog;
	_bound = new BoundingBox(ID,this);
	_position=position;
	_fallAccel = GRAVITY/10;

	_dir = Direction::Right;
	_state = FatFrogState::Falling;
	_player=p;
	_jumpTimer=0;
	_jumpTime = 2.0f;
	_jumpCount=0;
	_maxJumps=2;
}

BombFrogEnemy::~BombFrogEnemy()
{
	Enemy::~Enemy();
	_player = NULL;
}

bool BombFrogEnemy::Initialize(ObjectManager* om)
{
	return BombFrogEnemy::Initialize(om, ZERO_VECTOR);
}

bool BombFrogEnemy::Initialize(ObjectManager* om, D3DXVECTOR3 position)
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
		if(!objectImage.initialize(_om->GetGraphics(), FAT_FROG_WIDTH, FAT_FROG_HEIGHT, FAT_FROG_COLS, &objectTexture, 0.25f))
		{
			return false;
		}
		
		if(!_bound->Initialize(_om, ( objectImage.getHeight()-50)*objectImage.getScale(),objectImage.getWidth() * objectImage.getScale()))
		{
			return false;
		}
	}

	objectImage.setFrames(FAT_FROG_START_FRAME,FAT_FROG_END_FRAME);
	objectImage.setCurrentFrame(FAT_FROG_START_FRAME);
	objectImage.setFrameDelay(FAT_FROG_ANIMATION_DELAY);

	if(_state==FatFrogState::Dead)
		_state=FatFrogState::Falling;

	return true;
}

void BombFrogEnemy::Draw(COLOR_ARGB color)
{
	if(_state==FatFrogState::Dead)
		return;

	Enemy::Draw(color);
}

void BombFrogEnemy::Draw(SpriteData sd, COLOR_ARGB color)
{
	if(_state==FatFrogState::Dead)
		return;

	Enemy::Draw(sd,color);
}

void BombFrogEnemy::Update(float elapsedTime)
{
	if(_state==FatFrogState::Dead)
		return;


	if(_state == FatFrogState::Falling || _state==FatFrogState::Jumping)
		_velocity.y+=_fallAccel*elapsedTime*elapsedTime;
	
	if(_state == FatFrogState::Jumping && _velocity.y >0 && _jumpCount<_maxJumps)
	{
		//TEMP ANIMATION
			if(_dir==Direction::Left)
			{
				objectImage.flipHorizontal(false);
			}
			else
			{
				objectImage.flipHorizontal(true);
			}
		Jump();
	}

	if(_state == FatFrogState::Patrolling)
	{
		_jumpTimer+=elapsedTime;
		if(_jumpTimer>=_jumpTime)
		{
			_jumpTimer=0;
			_jumpTime= (rand()%4)+0.5f;
			_state=FatFrogState::Jumping;
			//TEMP ANIMATION
			if(_dir==Direction::Left)
			{
				objectImage.flipHorizontal(false);
			}
			else
			{
				objectImage.flipHorizontal(true);
			}

			Jump();
		}
	}
	Enemy::Update(elapsedTime);
}

void BombFrogEnemy::Jump()
{
	_jumpCount++;
	_velocity.y = -250;

	if(_dir==Direction::Left)
	{
		_velocity.x = -250;
	}
	else
	{
		_velocity.x = 250;
	}
}


void BombFrogEnemy::ProcessCollision(GameObject* obj)
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

	if(_state==FatFrogState::Dead)
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

void BombFrogEnemy::EnvironmentCollision(EnvironmentObject* obj)
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

void BombFrogEnemy::DefaultCollision(GameObject* obj)
{
}

void BombFrogEnemy::FloorCollision(EnvironmentObject* obj)
{
	//hit ceiling
	if(obj->GetPosition().y<_position.y)
		return;

	if(_state==FatFrogState::Jumping || _state==FatFrogState::Falling)
	{
		_velocity=ZERO_VECTOR;
		_state= FatFrogState::Patrolling;
		_jumpCount=0;
	}
}

void BombFrogEnemy::WallCollision(EnvironmentObject* obj)
{
	if(_state==FatFrogState::Jumping || _state==FatFrogState::Falling)
	{
		_velocity =ZERO_VECTOR;
		_state = FatFrogState::Patrolling;
		_jumpCount=1;
	}
}

void BombFrogEnemy::PlayerCollision(Player* obj)
{
	//damage player;
	_state = FatFrogState::Dead;
}

void BombFrogEnemy::AI()
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