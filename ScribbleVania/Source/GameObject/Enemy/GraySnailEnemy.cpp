#include "../../../Header/GameObject/Enemy/GraySnailEnemy.h"
#include "../../../Header/Collidable/BoundingBox.h"


GraySnailEnemy::GraySnailEnemy()
{
	_enemyType = EnemyType::GraySnail;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY;
	_accel = GRAY_SNAIL_PATROL_ACCEL;
	_dir = Direction::Right;
	_state=RedSnailState::Falling;
}

GraySnailEnemy::GraySnailEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p)
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

	_state=RedSnailState::Patrol;
	_player =p;
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
		
		if(!_bound->Initialize(_om, objectImage.getWidth() * objectImage.getScale(), objectImage.getHeight()*objectImage.getScale()))
		{
			return false;
		}
	}

	objectImage.setFrames(GRAY_SNAIL_START_FRAME_RIGHT, GRAY_SNAIL_END_FRAME_RIGHT);
	objectImage.setCurrentFrame(GRAY_SNAIL_START_FRAME_RIGHT);
	objectImage.setFrameDelay(GRAY_SNAIL_ANIMATION_DELAY);
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
		default:
			//bad state
			break;
	}

	AdjustImage();

	Enemy::Update(elapsedTime);
}

void GraySnailEnemy::UpdateAttack(float elapsedTime)
{
	//shoot bullet, 

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
	D3DXVECTOR3 direction = ExitObject(obj);

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

void GraySnailEnemy::PlayerCollision(Player* obj, D3DXVECTOR3 direction)
{
	WallCollision(NULL);
}

void GraySnailEnemy::EnvironmentCollision(EnvironmentObject* obj)
{
	switch(obj->GetSubType())
	{
		case EnvSubType::Door:
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

		//check if falling
		if(_velocity.x<0)
		{
			_dir=Direction::Left;
			return;
		}
		else if(_velocity.x>0)
		{
			_dir=Direction::Left;
			return;
		}

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
		
		float x = objectImage.getDegrees();
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

void GraySnailEnemy::WallCollision(EnvironmentObject* obj)
{
	if(_velocity.x <0)
	{
		_velocity.x =0;
		if(objectImage.isFlippedVertical())
		{
			_dir =Direction::Down;
			objectImage.setDegrees(270.0f);
		}
		else
		{
			_dir=  Direction::Up;
			objectImage.setDegrees(90.0f);
		}
	}
	else if (_velocity.x >0)
	{
		_velocity.x = 0;
		if(objectImage.isFlippedVertical())
		{
			_dir = Direction::Down;
			objectImage.setDegrees(90.0f);
		}
		else
		{
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
}