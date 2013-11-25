#include "../../../Header/GameObject/Enemy/SnailEnemy.h"
#include "../../../Header/Collidable/BoundingBox.h"

SnailEnemy::SnailEnemy() : Enemy()
{
	_velocity = ZERO_VECTOR;
	_enemyType = EnemyType::SnailEnemy;
	_bound = new BoundingBox(0,this);
	_fallAccel = GRAVITY;
}

SnailEnemy::SnailEnemy(unsigned int ID, D3DXVECTOR3 position) : Enemy(ID)
{
	_velocity = ZERO_VECTOR;
	_enemyType = EnemyType::SnailEnemy;

	_bound = new BoundingBox(ID,this);
	
	_position=position;
	_fallAccel = GRAVITY;
}


SnailEnemy::~SnailEnemy()
{
	Enemy::~Enemy();
}

bool SnailEnemy::Initialize(Game* game)
{
	return SnailEnemy::Initialize(game, D3DXVECTOR3(0,GAME_HEIGHT*0.8f, 1));
}

bool SnailEnemy::Initialize(Game* game,  D3DXVECTOR3 position)
{
	_game=game;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!objectTexture.initialize(_game->getGraphics(), SNAIL_IMAGE))
	{
		return false;
	}
	else
	{
		if(!objectImage.initialize(_game->getGraphics(), SNAIL_WIDTH, SNAIL_HEIGHT, SNAIL_COLS, &objectTexture))
		{
			return false;
		}
		
		if(!_bound->Initialize(_game, objectImage.getWidth(), objectImage.getHeight()))
		{
			return false;
		}
	}

	objectImage.setFrames(SNAIL_START_FRAME_RIGHT, SNAIL_END_FRAME_RIGHT);
	objectImage.setCurrentFrame(SNAIL_START_FRAME_RIGHT);
	objectImage.setFrameDelay(SNAIL_ANIMATION_DELAY);

	return true;
}

void SnailEnemy::Update(float elapsedTime)
{

	objectImage.setX(this->_position.x);
	objectImage.setY(this->_position.y);
	objectImage.update(elapsedTime);
	_bound->Update(elapsedTime);
}

void SnailEnemy::ProcessCollision(GameObject* obj)
{
	DefaultCollision(obj);
}

void SnailEnemy::DefaultCollision(GameObject* obj)
{
	D3DXVECTOR3 diff = this->GetCenter()-obj->GetCollidable()->GetNearestPoint(this->GetCenter());
	diff.z=0;
	D3DXVECTOR3 direction;

	if(diff.x==0 && diff.y==0)
	{
		D3DXVECTOR3 temp(this->GetVelocity().x *-1, this->GetVelocity().y *-1,0);
		D3DXVec3Normalize(&direction, &temp);
	}
	else
	{
		D3DXVec3Normalize(&direction,&diff);
	}

	bool vertNeg = this->_velocity.y <0;
	bool horzNeg = this->_velocity.x <0;
	while(this->_bound->Intersects(obj->GetCollidable()))
	{
		this->_position+=direction*0.1f;

		if(vertNeg && this->_velocity.y!=0)
		{
			this->_velocity.y+=10;
			this->_velocity.y= this->_velocity.y>0?0:this->_velocity.y;
		}
		else if(this->_velocity.y!=0)
		{
			this->_velocity.y-=10;
			this->_velocity.y = this->_velocity.y<0?0:this->_velocity.y;
		}
	}
}
void SnailEnemy::AI()
{
}


