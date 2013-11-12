#include "Player.h"

Player::Player() : GameObject()
{
	_accel = 250000;
	_jumpCount =1;
	_jumpMax = 1;
	_fallAccel = 981000;
	_onLeft = true;
	_state = PlayerState::jumping;
	_type = ObjectType::Player;
	_velocity = ZERO_VECTOR;
	_position = ZERO_VECTOR;
	_type = ObjectType::Player;
	_bound = new BoundingBox(0, this);
}

Player::Player(unsigned int id) : GameObject(id)
{
	_accel = 250000;
	_fallAccel = 981000;
	_jumpCount=1;
	_jumpMax=1;
	_onLeft = true;
	_state = PlayerState::jumping;
	_type = ObjectType::Player;
	_velocity= ZERO_VECTOR;
	_position= ZERO_VECTOR;
	_type = ObjectType::Player;
	_bound = new BoundingBox(id,this);
}

Player::Player(unsigned int id,D3DXVECTOR3 position):GameObject(id)
{
	_accel = 250000;
	_jumpCount =1;
	_jumpMax = 1;
	_onLeft = true;
	_fallAccel = 98100;
	_state = PlayerState::jumping;
	_type = ObjectType::Player;
	_velocity= ZERO_VECTOR;
	_position= position;
	_type = ObjectType::Player;
	_bound = new BoundingBox(id,this);
}

Player::~Player()
{
	_game=NULL; 
	 SAFE_DELETE(_bound);
	_bound=NULL;
}

bool Player::Initialize(Game* game)
{
	return Player::Initialize(game, _position==NULL?ZERO_VECTOR:_position);
}

bool Player::Initialize(Game* game, D3DXVECTOR3 position)
{
	_game = game;
	_position = position;

	if(!playerTexture.initialize(_game->getGraphics(), SHIP_IMAGE))
	{
		return false;
	}
	else
	{
		if(!playerImage.initialize(_game->getGraphics(), SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &playerTexture))
		{
			return false;
		}
			playerImage.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames
			playerImage.setCurrentFrame(SHIP_START_FRAME);     // starting frame
			playerImage.setFrameDelay(SHIP_ANIMATION_DELAY);

			if(!_bound->Initialize(game, this->GetWidth(), this->GetHeight()))
			{
				return false;
			}
	}
	return true;
}
void Player::Shutdown()
{
	_bound->Shutdown();
	playerTexture.onLostDevice();
}

void Player::Update(float elapsedTime)
{
	//Update image frame if necessary

	Input* input = _game->getInput();

	switch(_state)
	{
	case PlayerState::jumping:
		UpdateJumping(elapsedTime,input);
		break;
	case PlayerState::sliding:
		UpdateSliding(elapsedTime,input);
		break;
	default: //walking
		UpdateWalking(elapsedTime,input);
		break;
	}
	

	if(_velocity.x<(MAX_PLAYER_SPEED*-1))
	{
		_velocity.x = MAX_PLAYER_SPEED *-1;
	}
	else if(_velocity.x > MAX_PLAYER_SPEED)
	{
		_velocity.x = MAX_PLAYER_SPEED;
	}
	

	 if (_position.y> GAME_HEIGHT)              // if off screen bottom
            _position.y = (float)-playerImage.getHeight();    // position off screen top
	 if (_position.y < -playerImage.getHeight())        // if off screen top
            _position.y = (float)GAME_HEIGHT;          // position off screen bottom
	  if (_position.x < -playerImage.getWidth())         // if off screen left
            _position.x = (float)GAME_WIDTH;           // position off screen right
	  if (_position.x > GAME_WIDTH)               // if off screen right
            _position.x = (float)-playerImage.getWidth();     // position off screen left

	_position.x += _velocity.x * elapsedTime;
	_position.y += _velocity.y * elapsedTime;

	

	playerImage.setX(_position.x);
	playerImage.setY(_position.y);
    playerImage.update(elapsedTime);
	_bound->Update(elapsedTime);
	input=NULL;
}

void Player::UpdateJumping(float elapsedTime,Input* input)
{
	_velocity.y += _fallAccel*elapsedTime*elapsedTime;

		if(input->isKeyDown(PLAYER_RIGHT_KEY))            // if accel right
		{
			_velocity.x += _accel*elapsedTime*elapsedTime*0.25f;
		}
		if(input->isKeyDown(PLAYER_LEFT_KEY))             // if accel left
		{
			_velocity.x -= _accel*elapsedTime*elapsedTime*0.25f;
		}
		if(input->isKeyDown(PLAYER_UP_KEY))               // if accel up
		{
			if(_velocity.y>=0 && _jumpCount<_jumpMax)
			{
				_velocity.y =-350;
				_jumpCount++;
			}
		}
}

void Player::UpdateWalking(float elapsedTime,Input* input)
{
	_velocity.y += _fallAccel*elapsedTime*elapsedTime;
	if(input->isKeyDown(PLAYER_RIGHT_KEY))            // if accel right
		{
			_velocity.x += _accel*elapsedTime*elapsedTime;
		}
		if(input->isKeyDown(PLAYER_LEFT_KEY))             // if accel left
		{
			_velocity.x -= _accel*elapsedTime*elapsedTime;
		}

		if(input->isKeyDown(PLAYER_UP_KEY))               // if accel up
		{
			_velocity.y =-350;
			_jumpCount=0;
			_state = PlayerState::jumping;
		}

		if(!input->isKeyDown(PLAYER_LEFT_KEY) && !input->isKeyDown(PLAYER_RIGHT_KEY))
		{
			if(_velocity.x <0)
			{
				_velocity.x += _accel*0.5f*elapsedTime*elapsedTime;
				_velocity.x = (_velocity.x <0)? _velocity.x : 0;
			}
			else if(_velocity.x >0)
			{
				_velocity.x -= _accel*0.5f*elapsedTime*elapsedTime;
				_velocity.x = (_velocity.x >0)? _velocity.x : 0;
			}
		}
}

void Player::UpdateSliding(float elapsedTime,Input* input)
{
	if(input->isKeyDown(PLAYER_DOWN_KEY))             // if accel down
	{
		_velocity.y += _fallAccel*elapsedTime*elapsedTime;
	}
	else
	{
		_velocity.y += _fallAccel*0.25f*elapsedTime*elapsedTime;
	}

	if(input->isKeyDown(PLAYER_UP_KEY))
	{
		if(_onLeft)
		{
			this->_velocity.x=+250;	
		}
		else
		{
			this->_velocity.x=-250;
		}

		this->_velocity.y =-350;
		_jumpCount=0;
		_state = PlayerState::jumping;
	}
}

void Player::ProcessCollision(GameObject* obj)
{
	//_state = PlayerState::walking;

	switch (obj->GetObjectType())
	{
		case ObjectType::FloorEnvironment:
			FloorCollision((EnvironmentObject*)obj);
			break;
		case ObjectType::WallEnvironment:
			WallCollision((EnvironmentObject*)obj);
			break;
		default:
			DefaultCollision(obj);
			break;
	}
}


void Player::DefaultCollision(GameObject* obj)
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

		if(this->_velocity.y==0)
			_state=PlayerState::walking;
	}
}

void Player::FloorCollision(EnvironmentObject* obj)
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
	}
	this->_velocity.y=0;
	_state=PlayerState::walking;
}

void Player::WallCollision(EnvironmentObject* obj)
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
	}
	_velocity.x=0;
	_velocity.y=0;

	if(direction.x<0)
	{
		_onLeft=false;
	}
	else
	{
		_onLeft=true;
	}
	_state=PlayerState::sliding;
}

void Player::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	playerImage.draw(color);
}

void Player::Draw(SpriteData sd, COLOR_ARGB color)
{
	_bound->Draw(sd,color);
	playerImage.draw(sd,color);
}

void Player::Reset()
{
	playerTexture.onResetDevice();
	_bound->Reset();
}

int Player::GetWidth()
{
	return playerImage.getWidth();
}

int Player::GetHeight()
{
	return playerImage.getHeight();
}

D3DXVECTOR3 Player::GetCenter()
{
	D3DVECTOR temp;
	temp.x = playerImage.getCenterX();
	temp.y = playerImage.getCenterY();
	temp.z= this->GetPosition().z;
	return temp;
}
