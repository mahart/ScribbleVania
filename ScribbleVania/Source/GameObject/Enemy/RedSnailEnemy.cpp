#include "../../../Header/GameObject/Enemy/RedSnailEnemy.h"
#include "../../../Header/Collidable/BoundingBox.h"

RedSnailEnemy::RedSnailEnemy() : Enemy()
{
	_enemyType = EnemyType::RedSnail;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY;
	_accel = RED_SNAIL_PATROL_ACCEL;
	_dir = Direction::Right;
	_state=RedSnailState::Patrol;
}

RedSnailEnemy::RedSnailEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p) : Enemy(ID)
{
	_enemyType = EnemyType::RedSnail;

	_bound = new BoundingBox(ID,this);
	
	_position=position;
	_fallAccel = GRAVITY;
	_accel = RED_SNAIL_PATROL_ACCEL;
	_dir = Direction::Right;
	_state=RedSnailState::Patrol;
	_player =p;
}


RedSnailEnemy::~RedSnailEnemy()
{
	Enemy::~Enemy();
	_player = NULL;
}

bool RedSnailEnemy::Initialize(ObjectManager* om)
{
	return RedSnailEnemy::Initialize(om, D3DXVECTOR3(0,GAME_HEIGHT*0.8f, 1));
}

bool RedSnailEnemy::Initialize(ObjectManager* om,  D3DXVECTOR3 position)
{
	_om=om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!objectTexture.initialize(_om->GetGraphics(), RED_SNAIL_IMAGE))
	{
		return false;
	}
	else
	{
		if(!objectImage.initialize(_om->GetGraphics(), RED_SNAIL_WIDTH, RED_SNAIL_HEIGHT, RED_SNAIL_COLS, &objectTexture,0.5f))
		{
			return false;
		}
		
		if(!_bound->Initialize(_om, objectImage.getWidth() * objectImage.getScale(), objectImage.getHeight()*objectImage.getScale()))
		{
			return false;
		}
	}

	objectImage.setFrames(RED_SNAIL_START_FRAME_RIGHT, RED_SNAIL_END_FRAME_RIGHT);
	objectImage.setCurrentFrame(RED_SNAIL_START_FRAME_RIGHT);
	objectImage.setFrameDelay(RED_SNAIL_ANIMATION_DELAY);

	return true;
}

void RedSnailEnemy::Update(float elapsedTime)
{
	_velocity.y += _fallAccel*elapsedTime*elapsedTime;

	switch(_dir)
	{
		case Direction::Left:
			_velocity.x -= _accel*elapsedTime*elapsedTime;
			break;
		case Direction::Right:
			_velocity.x += _accel*elapsedTime*elapsedTime;
			break;
		default:
			break;
	}

	if(_state==RedSnailState::Patrol)
	{
		if(_velocity.x<(MAX_RED_SNAIL_MOVE_SPEED*-1))
		{
			_velocity.x = MAX_RED_SNAIL_MOVE_SPEED *-1;
		}
		else if(_velocity.x > MAX_RED_SNAIL_MOVE_SPEED)
		{
			_velocity.x = MAX_RED_SNAIL_MOVE_SPEED;
		}
	}
	else if(_state == RedSnailState::Attack)
	{
		if(_velocity.x<(MAX_RED_SNAIL_ATTACK_SPEED*-1))
		{
			_velocity.x = MAX_RED_SNAIL_ATTACK_SPEED *-1;
		}
		else if(_velocity.x > MAX_RED_SNAIL_ATTACK_SPEED)
		{
			_velocity.x = MAX_RED_SNAIL_ATTACK_SPEED;
		}
	}

	Enemy::Update(elapsedTime);
}

void RedSnailEnemy::ProcessCollision(GameObject* obj)
{
	D3DXVECTOR3 direction;
	if(obj->GetObjectType()!=ObjectType::Projectile)
		direction = ExitObject(obj);
	switch(obj->GetObjectType())
	{
		case ObjectType::Player:
			PlayerCollision((Player*)obj, direction);
			break;
		case ObjectType::EnvironmentObject:
			EnvironmentCollision((EnvironmentObject*)obj);
			break;
		default:
			DefaultCollision(obj);
	}
}

void RedSnailEnemy::PlayerCollision(Player* obj, D3DXVECTOR3 direction)
{
	if(_dir == Direction::Left)
	{
		if(direction.x <0)
		{
			obj->VBounce(D3DXVECTOR3(500,-50,0));
		}
		else
		{
			obj->VBounce(D3DXVECTOR3(-100,-50,0));
		}
		_dir = Direction::Right;
		objectImage.setFrames(RED_SNAIL_START_FRAME_RIGHT, RED_SNAIL_END_FRAME_RIGHT);
		_velocity.x=0;
	}
	else if (_dir == Direction::Right)
	{
		if(direction.x >0)
		{
			obj->VBounce(D3DXVECTOR3(-500,-50,0));
		}
		else
		{
			obj->VBounce(D3DXVECTOR3(100,-50,0));
		}
		_dir = Direction::Left;
		objectImage.setFrames(RED_SNAIL_START_FRAME_LEFT, RED_SNAIL_END_FRAME_LEFT);
		_velocity.x=0;
	}

	bool vertNeg = _velocity.y <0;

	if(vertNeg && _velocity.y!=0)
	{
		_velocity.y+=10;
		_velocity.y= _velocity.y>0?0:_velocity.y;
	}
	else if(_velocity.y!=0)
	{
		_velocity.y-=10;
		_velocity.y = _velocity.y<0?0:_velocity.y;
	}
}

void RedSnailEnemy::EnvironmentCollision(EnvironmentObject* obj)
{
	switch(obj->GetSubType())
	{
		case EnvSubType::Floor:
			FloorCollision(obj);
			break;
		case EnvSubType::Door:
		case EnvSubType::Ledge:
		case EnvSubType::Other:
		case EnvSubType::Wall:
			WallCollision(obj);
			break;
		default:
			DefaultCollision(obj);
	}
}

void RedSnailEnemy::FloorCollision(EnvironmentObject* obj)
{
	_velocity.y=0;	
}

void RedSnailEnemy::WallCollision(EnvironmentObject* obj)
{
	D3DXVECTOR3 diff = GetCenter()-obj->GetCollidable()->GetNearestPoint(GetCenter());
	diff.z=0;

	if(_dir == Direction::Left)
	{
		_dir = Direction::Right;
		objectImage.setFrames(RED_SNAIL_START_FRAME_RIGHT, RED_SNAIL_END_FRAME_RIGHT);
		_velocity.x=0;
	}
	else if (_dir == Direction::Right)
	{
		_dir = Direction::Left;
		objectImage.setFrames(RED_SNAIL_START_FRAME_LEFT, RED_SNAIL_END_FRAME_LEFT);
		_velocity.x=0;
	}

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

	bool vertNeg = _velocity.y <0;
	bool horzNeg = _velocity.x <0;
	while(_bound->Intersects(obj->GetCollidable()))
	{
		_position+=direction*0.1f;

		if(vertNeg && _velocity.y!=0)
		{
			_velocity.y+=10;
			_velocity.y= _velocity.y>0?0:_velocity.y;
		}
		else if(_velocity.y!=0)
		{
			_velocity.y-=10;
			_velocity.y = _velocity.y<0?0:_velocity.y;
		}
	}
}



void RedSnailEnemy::DefaultCollision(GameObject* obj)
{
	D3DXVECTOR3 diff = GetCenter()-obj->GetCollidable()->GetNearestPoint(GetCenter());
	diff.z=0;
	//this->_velocity.y=0;
	if(_dir == Direction::Left)
	{
		_dir = Direction::Right;
		objectImage.setFrames(RED_SNAIL_START_FRAME_RIGHT, RED_SNAIL_END_FRAME_RIGHT);
		_velocity.x=0;
	}
	else if (_dir == Direction::Right)
	{
		_dir = Direction::Left;
		objectImage.setFrames(RED_SNAIL_START_FRAME_LEFT, RED_SNAIL_END_FRAME_LEFT);
		_velocity.x=0;
	}

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

	bool vertNeg = _velocity.y <0;
	bool horzNeg = _velocity.x <0;
	while(_bound->Intersects(obj->GetCollidable()))
	{
		_position+=direction*0.1f;

		if(vertNeg && _velocity.y!=0)
		{
			_velocity.y+=10;
			_velocity.y= _velocity.y>0?0:_velocity.y;
		}
		else if(_velocity.y!=0)
		{
			_velocity.y-=10;
			_velocity.y = _velocity.y<0?0:_velocity.y;
		}
	}
}

void RedSnailEnemy::AI()
{
	if(_state==RedSnailState::Falling || _state == RedSnailState::Dead)
		return;

	float diffX = _position.x - _player->GetPosition().x;
	float diffY = _position.y - _player->GetPosition().y;

	float distSqr = (diffX*diffX)+(diffY*diffY);
	float aggroSqr = (RED_SNAIL_AGGRO_RADIUS*RED_SNAIL_AGGRO_RADIUS)+(RED_SNAIL_AGGRO_RADIUS*RED_SNAIL_AGGRO_RADIUS);
	
	bool isVisible = false;

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

	if(distSqr < aggroSqr && isVisible)
	{
		_state = RedSnailState::Attack;
		_accel = RED_SNAIL_ATTACK_ACCEL;
		objectImage.setFrameDelay(RED_SNAIL_ANIMATION_DELAY/4);
	}
	else
	{
		_state = RedSnailState::Patrol;
		_accel = RED_SNAIL_PATROL_ACCEL;
		objectImage.setFrameDelay(RED_SNAIL_ANIMATION_DELAY);
	}
	
}


