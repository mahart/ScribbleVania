#include "../../../Header/GameObject/Enemy/GraySnailEnemy.h"
#include "../../../Header/Collidable/BoundingBox.h"


GraySnailEnemy::GraySnailEnemy() : Enemy()
{
	_enemyType = EnemyType::GraySnail;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY;
	_accel = GRAY_SNAIL_PATROL_ACCEL;
	_dir = Direction::Right;
	_state=RedSnailState::Falling;
	_shot=false;
	_hitPoints = GRAY_SNAIL_HP;
}

GraySnailEnemy::GraySnailEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p) : Enemy(ID)
{
	_enemyType = EnemyType::GraySnail;

	_bound = new BoundingBox(ID,this);
	
	_position=position;
	//_position.x+=20;
	_fallAccel = GRAVITY;
	_accel = GRAY_SNAIL_PATROL_ACCEL;

	if(_position.x > GAME_WIDTH/2)
		_dir = Direction::Right;
	else
		_dir = Direction::Left;

	_state=RedSnailState::Falling;
	_player =p;
	_shot=false;
	_hitPoints = GRAY_SNAIL_HP;
}

GraySnailEnemy::~GraySnailEnemy()
{
	Enemy::~Enemy();
	_player=NULL;
}

bool GraySnailEnemy::Initialize(ObjectManager* om)
{
	return GraySnailEnemy::Initialize(om,D3DXVECTOR3(0,GAME_HEIGHT*0.8f, 1));
}

bool GraySnailEnemy::Initialize(ObjectManager* om,  D3DXVECTOR3 position)
{
	_om = om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!objectTexture.initialize(_om->GetGraphics(), GRAY_SNAIL_IMAGE))
	{
		return false;
	}
	else
	{
		if(!objectImage.initialize(_om->GetGraphics(), GRAY_SNAIL_WIDTH, GRAY_SNAIL_HEIGHT, GRAY_SNAIL_COLS, &objectTexture,1.0f))
		{
			return false;
		}
		
		if(!_bound->Initialize(_om,objectImage.getHeight()*objectImage.getScale(), objectImage.getWidth() * objectImage.getScale()))
		{
			return false;
		}
	}

	objectImage.setFrames(GRAY_SNAIL_START_FRAME_RIGHT, GRAY_SNAIL_END_FRAME_RIGHT);
	objectImage.setCurrentFrame(GRAY_SNAIL_START_FRAME_RIGHT);
	objectImage.setFrameDelay(GRAY_SNAIL_ANIMATION_DELAY);

	_hitPoints = GRAY_SNAIL_HP;

	if(_state == RedSnailState::Dead)
		_state = RedSnailState::Falling;

	return true;
}

void GraySnailEnemy::AdjustImage()
{
	if(_velocity.y!=0)
		return;

	if(_velocity.x <0)
	{
		objectImage.flipHorizontal(true);
	}
	else
	{
		objectImage.flipHorizontal(false);
	}
}

void GraySnailEnemy::Update(float elapsedTime)
{
	switch(_state)
	{
		case RedSnailState::Attack:
			UpdateAttack(elapsedTime);
			break;
		case RedSnailState::Falling:
			UpdateFalling(elapsedTime);
			break;
		case RedSnailState::Patrol:
			UpdatePatrol(elapsedTime);
			break;
		case RedSnailState::Dead:
			return;
		default:
			//bad state
			break;
	}

	AdjustImage();

	Enemy::Update(elapsedTime);
}

void GraySnailEnemy::UpdateAttack(float elapsedTime)
{
	UpdatePatrol(elapsedTime);
	int cur = objectImage.getCurrentFrame();
	if(cur!=GRAY_SNAIL_SHOT_FRAME1 && cur!=GRAY_SNAIL_SHOT_FRAME2)
	{
		_shot=false;
		return;	
	}

	if(!_shot)
	{
		_om->AddObject(new BoringProjectile(_om->GetNextID(), this));
		_shot = true;
	}
}


D3DXVECTOR3 GraySnailEnemy::GetDirection()
{
	//shoot bullet, 
	D3DXVECTOR3 diff = _player->GetCollidable()->GetNearestPoint(GetCenter())-GetCenter();
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
	return direction;
}

void GraySnailEnemy::UpdateFalling(float elapsedTime)
{
	_velocity.y += _fallAccel*elapsedTime*elapsedTime;
}

void GraySnailEnemy::UpdatePatrol(float elapsedTime)
{
	switch(_dir)
	{
		case Direction::Right:
			_velocity.x += _accel*elapsedTime*elapsedTime;
			break;
		case Direction::Up:
			_velocity.y -= _accel*elapsedTime*elapsedTime;
			break;
		case Direction::Left:
			_velocity.x -=_accel*elapsedTime*elapsedTime;
			break;
		case Direction::Down:
			_velocity.y +=_accel*elapsedTime*elapsedTime;
			break;
		default:
			//bad direction
			break;
	}

	if(_velocity.x<(MAX_RED_SNAIL_MOVE_SPEED*-1))
	{
		_velocity.x = MAX_RED_SNAIL_MOVE_SPEED *-1;
	}
	else if(_velocity.x > MAX_RED_SNAIL_MOVE_SPEED)
	{
		_velocity.x = MAX_RED_SNAIL_MOVE_SPEED;
	}

	if(_velocity.y<(MAX_RED_SNAIL_MOVE_SPEED*-1))
	{
		_velocity.y = MAX_RED_SNAIL_MOVE_SPEED *-1;
	}
	else if(_velocity.y > MAX_RED_SNAIL_MOVE_SPEED)
	{
		_velocity.y = MAX_RED_SNAIL_MOVE_SPEED;
	}
}

void GraySnailEnemy::ProcessCollision(GameObject* obj)
{
	D3DXVECTOR3 direction;
	
	if(obj->GetObjectType()!=ObjectType::Projectile)
		direction= ExitObject(obj);

	if(_state == RedSnailState::Dead)
		return;

	switch(obj->GetObjectType())
	{
		case ObjectType::Player:
			PlayerCollision((Player*)obj, direction);
			break;
		case ObjectType::EnvironmentObject:
			EnvironmentCollision((EnvironmentObject*)obj);
			break;
		case ObjectType::Projectile:
			ProjectileCollision((Projectile*)obj);
			break;
		default:
			DefaultCollision(obj);
	}
}

void GraySnailEnemy::PlayerCollision(Player* obj, D3DXVECTOR3 direction)
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

void GraySnailEnemy::EnvironmentCollision(EnvironmentObject* obj)
{
	switch(obj->GetSubType())
	{
		case EnvSubType::Door:
		case EnvSubType::Ledge:
		case EnvSubType::Wall:
			WallCollision(obj);
			break;
		case EnvSubType::Floor:
			FloorCollision(obj);
			break;
		default:
			//do nothing
			break;
	}
}

void GraySnailEnemy::FloorCollision(EnvironmentObject* obj)
{
	if(_velocity.y <0)
	{
		_velocity.y=0;

		if(objectImage.getDegrees()==270.0f)
		{
			objectImage.setDegrees(0.0f);
			objectImage.flipVertical(true);
			_dir=Direction::Left;
		}
		else if(objectImage.getDegrees()==90.0f)
		{
			objectImage.setDegrees(0.0f);
			objectImage.flipVertical(true);
			_dir=Direction::Right;
		}

	}
	else if(_velocity.y>0)
	{
		_velocity.y=0;
		//check if falling
		if(_state == RedSnailState::Falling)
		{
			objectImage.setDegrees(0.0f);
			objectImage.flipVertical(false);

			if(_player->GetPosition().x>_position.x)
				_dir = Direction::Right;
			else
				_dir = Direction::Left;
			/*
			if(_oldDir!=Direction::Up && _oldDir!=Direction::Down)
				_dir = _oldDir;
			else
				_dir=Direction::Left;
				*/
			_state=RedSnailState::Patrol;
			return;
		}
		

		if(objectImage.getDegrees()==270.0f)
		{
			objectImage.setDegrees(0.0f);
			objectImage.flipVertical(false);
			_dir=Direction::Right;
		}
		else if(objectImage.getDegrees()==90.0f)
		{
			objectImage.setDegrees(0.0f);
			objectImage.flipVertical(false);
			_dir=Direction::Left;
		}
	}

	//else incidintal collision. just keep moving.
}

void GraySnailEnemy::ProjectileCollision(Projectile* obj)
{
	_hitPoints--;
	if((_dir == Direction::Left || _dir == Direction::Right) && !objectImage.isFlippedVertical())
		return;
	_state = RedSnailState::Falling;
	objectImage.setDegrees(0.0f);

}

void GraySnailEnemy::WallCollision(EnvironmentObject* obj)
{
	if(_velocity.x <0)
	{
		_velocity.x =0;
		if(objectImage.isFlippedVertical())
		{
			_oldDir=_dir;
			_dir =Direction::Down;
			objectImage.setDegrees(270.0f);
		}
		else
		{
			_oldDir=_dir;
			_dir=  Direction::Up;
			objectImage.setDegrees(90.0f);
		}
	}
	else if (_velocity.x >0)
	{
		_velocity.x = 0;
		if(objectImage.isFlippedVertical())
		{
			_oldDir=_dir;
			_dir = Direction::Down;
			objectImage.setDegrees(90.0f);
		}
		else
		{
			_oldDir=_dir;
			_dir= Direction::Up;
			objectImage.setDegrees(270.0f);
		}
	}
}

void GraySnailEnemy::DefaultCollision(GameObject* obj)
{
}

void GraySnailEnemy::AI()
{
	if(_hitPoints<=0)
	{
		_state = RedSnailState::Dead;
	}

	if(_state==RedSnailState::Falling || _state == RedSnailState::Dead)
		return;

	float diffX = _position.x - _player->GetPosition().x;
	float diffY = _position.y - _player->GetPosition().y;

	float distSqr = (diffX*diffX)+(diffY*diffY);
	float aggroSqr = (RED_SNAIL_AGGRO_RADIUS*RED_SNAIL_AGGRO_RADIUS)+(RED_SNAIL_AGGRO_RADIUS*RED_SNAIL_AGGRO_RADIUS);
	
	/*bool isVisible = false;
	
	if(_dir == Direction::Left && diffX>0)
	{
		if(diffY <100 && diffY>-75)
		{
			isVisible = true;
		}
	}
	else if(_dir == Direction::Right && diffX<0)
	{
		if(diffY <100 && diffY>-75)
		{
			isVisible =true;
		}
	}
	*/
	if(distSqr < aggroSqr)
	{
		_state = RedSnailState::Attack;
		//_accel = RED_SNAIL_ATTACK_ACCEL;
		//objectImage.setFrameDelay(RED_SNAIL_ANIMATION_DELAY/4);
	}
	else
	{
		_state = RedSnailState::Patrol;
		//_accel = RED_SNAIL_PATROL_ACCEL;
		//objectImage.setFrameDelay(RED_SNAIL_ANIMATION_DELAY);
	}
}