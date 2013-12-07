#include "../../../Header/GameObject/Player/Player.h"
#include "../../../Header/ObjectManager.h"
#include "../../../Header/GameObject/Projectile.h"

Player::Player() : GameObject()
{
	_accel = PLAYER_ACCEL;
	_jumpCount =1;
	_jumpMax = 1;
	_fallAccel = GRAVITY;
	_onLeft = true;
	_state = PlayerState::Jumping;
	_type = ObjectType::Player;
	_velocity = ZERO_VECTOR;
	_position = ZERO_VECTOR;
	_type = ObjectType::Player;
	_bound = new BoundingBox(0, this);
	_climbing = false;
	_shotTimer=0;
}

Player::Player(unsigned int id) : GameObject(id)
{
	_accel = PLAYER_ACCEL;
	_fallAccel = GRAVITY;
	_jumpCount=1;
	_jumpMax=1;
	_onLeft = true;
	_state = PlayerState::Jumping;
	_type = ObjectType::Player;
	_velocity= ZERO_VECTOR;
	_position= ZERO_VECTOR;
	_type = ObjectType::Player;
	_bound = new BoundingBox(id,this);
	_climbing = false;
	_shotTimer=0;
}

Player::Player(unsigned int id,D3DXVECTOR3 position, ObjectManager* om):GameObject(id)
{
	_accel = PLAYER_ACCEL;
	_jumpCount =1;
	_jumpMax = 1;
	_onLeft = true;
	_fallAccel = 98100;
	_state = PlayerState::Jumping;
	_type = ObjectType::Player;
	_velocity= ZERO_VECTOR;
	_position= position;
	_type = ObjectType::Player;
	_bound = new BoundingBox(id,this);
	_climbing = false;
	_om = om;
	_shotTimer=0;
}

Player::~Player()
{
	Shutdown();
	_om=NULL; 
	 SAFE_DELETE(_bound);
	_bound=NULL;
}

bool Player::Initialize(ObjectManager* om)
{
	return Player::Initialize(om, _position==NULL?ZERO_VECTOR:_position);
}

bool Player::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om = om;
	_position = position;

	if(!playerTexture.initialize(_om->GetGraphics(), SHIP_IMAGE))
	{
		return false;
	}
	else
	{
		if(!playerImage.initialize(_om->GetGraphics(), SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &playerTexture,1.0f))
		{
			return false;
		}

		if(!_bound->Initialize(_om,(unsigned int)(GetWidth()*playerImage.getScale()),(unsigned int)(GetHeight()*playerImage.getScale())))
		{
			return false;
		}
	}

	playerImage.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	playerImage.setCurrentFrame(SHIP_START_FRAME);
	playerImage.setFrameDelay(SHIP_ANIMATION_DELAY);
	return true;
}

void Player::Shutdown()
{
	_bound->Shutdown();
	playerTexture.onLostDevice();
}



void Player::Update(float elapsedTime)
{
	Input* input = _om->GetInput();
	if(input->isKeyDown(PLAYER_UP_KEY))
	{   
		//Looking up
		if(playerImage.isFlippedHorizontal()) //&left
		{
			playerImage.setDegrees(45.0f);
		}
		else
		{
			playerImage.setDegrees(315.0f); //&Right
		}
	}
	else if(input->isKeyDown(PLAYER_DOWN_KEY)) 
	{
		//Looking Downs
		if(playerImage.isFlippedHorizontal()) //&left
		{
			playerImage.setDegrees(315.0f);
		}
		else
		{
			playerImage.setDegrees(45.0f); //&right
		}
	}
	else
	{
		playerImage.setDegrees(0.0f);
	}

	switch(_state)
	{
		case PlayerState::Jumping:
			UpdateJumping(elapsedTime,input);
			break;
		case PlayerState::Sliding:
			UpdateSliding(elapsedTime,input);
			break;
		case PlayerState::Hanging:
			UpdateHanging(elapsedTime, input);
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

	_position += _velocity * elapsedTime;
	

	playerImage.setX(_position.x);
	playerImage.setY(_position.y);

    playerImage.update(elapsedTime);
	_bound->Update(elapsedTime);

	input=NULL;
}

void Player::UpdateJumping(float elapsedTime,Input* input)
{
	_velocity.y += _fallAccel*elapsedTime*elapsedTime;
	_shotTimer-=elapsedTime;
	if(input->isKeyDown(PLAYER_SHOOT_KEY) && _shotTimer<=0)
	{
		_om->AddObject(new BoringProjectile(_om->GetNextID(), this));
		_shotTimer=0.25f;
	}

	if(input->isKeyDown(PLAYER_RIGHT_KEY))            // if accel right
	{
		_velocity.x += _accel*elapsedTime*elapsedTime*0.25f;
		playerImage.flipHorizontal(false);
	}
	if(input->isKeyDown(PLAYER_LEFT_KEY))             // if accel left
	{
		_velocity.x -= _accel*elapsedTime*elapsedTime*0.25f;
		playerImage.flipHorizontal(true);
	}
	if(input->isKeyDown(PLAYER_JUMP_KEY))               // if accel up
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
	_shotTimer-=elapsedTime;
	if(input->isKeyDown(PLAYER_SHOOT_KEY) && _shotTimer<=0)
	{
		_om->AddObject(new BoringProjectile(_om->GetNextID(), this));
		_shotTimer=0.25f;
	}

	if(input->isKeyDown(PLAYER_RIGHT_KEY))            // if accel right
		{
			_velocity.x += _accel*elapsedTime*elapsedTime;
			playerImage.flipHorizontal(false);
		}
		if(input->isKeyDown(PLAYER_LEFT_KEY))             // if accel left
		{
			_velocity.x -= _accel*elapsedTime*elapsedTime;
			playerImage.flipHorizontal(true);
		}

		if(input->isKeyDown(PLAYER_JUMP_KEY))               // if accel up
		{
			_velocity.y =-350;
			_jumpCount=0;
			_state = PlayerState::Jumping;
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

	if(input->isKeyDown(PLAYER_JUMP_KEY))
	{
		if(_onLeft)
		{
			_velocity.x=+250;	
			playerImage.flipHorizontal(false);
		}
		else
		{
			_velocity.x=-250;
			playerImage.flipHorizontal(true);
		}

		_velocity.y =-350;
		_jumpCount=0;
		_state = PlayerState::Jumping;
	}

	if(input->isKeyDown(PLAYER_LEFT_KEY))
	{
		if(!_onLeft)
		{
			_velocity.x -= _accel*elapsedTime*elapsedTime;
			_state = PlayerState::Jumping;
		}
	}

	if(input->isKeyDown(PLAYER_RIGHT_KEY))
	{
		if(_onLeft)
		{
			_velocity.x += _accel*elapsedTime*elapsedTime;
			_state= PlayerState::Jumping;
		}
	}
}

void Player::UpdateHanging(float elapsedTime, Input* input)
{
	_velocity.y =0;
	if(_climbing)
	{
		if(_position.y+GetHeight() > _touchedObj->GetPosition().y-2)
		{
			_velocity.y=-200;
			_velocity.x=0;
			return;
		}
		else
		{
			_velocity.y=0;
			if(_onLeft)
			{
				playerImage.flipHorizontal(true);
				if(_position.x + GetWidth() > _touchedObj->GetPosition().x + _touchedObj->GetWidth())
				{
					_velocity.x=-200;
					return;
				}
			}
			else
			{
				playerImage.flipHorizontal(false);
				if(_position.x < _touchedObj->GetPosition().x)
				{
					_velocity.x=200;
					return;
				}
			}
		}
		_climbing=false;
		_velocity.y=0;
		_state =PlayerState::Jumping;
	}
	else
	{
		if(input->isKeyDown(PLAYER_JUMP_KEY) && !input->wasKeyPressed(PLAYER_JUMP_KEY))
		{
			if(_onLeft)
			{
				_velocity.x=+250;	
			}
			else
			{
				_velocity.x=-250;
			}

			_velocity.y =-350;
			_jumpCount=0;
			_state = PlayerState::Jumping;
		}

		if(input->isKeyDown(PLAYER_UP_KEY))
		{
			_climbing = true;
		}

		if(input->isKeyDown(PLAYER_LEFT_KEY))
		{
			if(!_onLeft)
			{
				_velocity.x -= _accel*elapsedTime*elapsedTime;
				_state = PlayerState::Jumping;
			}
		}

		if(input->isKeyDown(PLAYER_RIGHT_KEY))
		{
			if(_onLeft)
			{
				_velocity.x += _accel*elapsedTime*elapsedTime;
				_state= PlayerState::Jumping;
			}
		}

		if(input->isKeyDown(PLAYER_DOWN_KEY))
		{
			_state= PlayerState::Sliding;
		}
	}
}

D3DXVECTOR3 Player::ExitObject(GameObject* obj)
{
	D3DXVECTOR3 diff = GetCenter()-obj->GetCollidable()->GetNearestPoint(GetCenter());
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

	while(_bound->Intersects(obj->GetCollidable()))
	{
		_position+=direction*0.1f;
	}
	return direction;
}

void Player::ProcessCollision(GameObject* obj)
{
	D3DXVECTOR3 dir = ExitObject(obj);
	switch (obj->GetObjectType())
	{
		case ObjectType::EnvironmentObject:
			EnvironmentCollision((EnvironmentObject*)obj, dir);
			break;
		default:
			DefaultCollision(obj);
			break;
	}
}


void Player::DefaultCollision(GameObject* obj)
{
	/*D3DXVECTOR3 diff = this->GetCenter()-obj->GetCollidable()->GetNearestPoint(this->GetCenter());
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
	}*/

	bool vertNeg = _velocity.y <0;
	bool horzNeg = _velocity.x <0;
	/*while(this->_bound->Intersects(obj->GetCollidable()))
	{
		this->_position+=direction*0.1f;
		*/
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

	if(_velocity.y==0)
		_state=PlayerState::Walking;
	//}
}

void Player::EnvironmentCollision(EnvironmentObject* obj, D3DXVECTOR3 direction)
{
	switch(obj->GetSubType())
	{
		case EnvSubType::Wall:
			WallCollision(obj, direction);
			break;
		case EnvSubType::Floor:
			FloorCollision(obj);
			break;
		case EnvSubType::Ledge:
			LedgeCollision(obj, direction);
			break;
		case EnvSubType::Door:
			DoorCollision((Door*)obj);
			break;
		case EnvSubType::Ceiling:
		case EnvSubType::Background:
		default:
			DefaultCollision(obj);
			break;
	}
}




void Player::FloorCollision(EnvironmentObject* obj)
{
	/*D3DXVECTOR3 diff = this->GetCenter()-obj->GetCollidable()->GetNearestPoint(this->GetCenter());
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
	}*/

	_velocity.y=0;
	if(_position.y < obj->GetPosition().y)
	{	
		_state=PlayerState::Walking;
	}
	
}

void Player::WallCollision(EnvironmentObject* obj, D3DXVECTOR3 direction)
{
	/*
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
	*/

	/*
	while(this->_bound->Intersects(obj->GetCollidable()))
	{
		this->_position+=direction*0.1f;
	}*/

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
	_state=PlayerState::Sliding;
}

void Player::LedgeCollision(EnvironmentObject* obj,D3DXVECTOR3 direction)
{
	/*D3DXVECTOR3 diff = this->GetCenter()-obj->GetCollidable()->GetNearestPoint(this->GetCenter());
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

	while(this->_bound->Intersects(obj->GetCollidable()))
	{
		this->_position+=direction*0.1f;
	}
	*/

	_touchedObj = obj;
	_velocity.y=0;
	if(_position.y < obj->GetCenter().y)
	{
		_state = PlayerState::Hanging;
		_velocity.x=0;
	}
	else
	{
		_state = PlayerState::Sliding;
	}

	if(direction.x<0)
	{
		_onLeft=false;
		playerImage.flipHorizontal(true);
	}
	else
	{
		_onLeft=true;
		playerImage.flipHorizontal(false);
	}
}

void Player::DoorCollision(Door* door)
{
	if(!door->IsOpen())
		return;

	Room* r = door->GetRoom();
	_om->LoadRoom(door->GetRoom());
	_position.x = door->GetExit().x;
	_position.y = door->GetExit().y;
	_velocity = ZERO_VECTOR;
}

void Player::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	playerImage.draw(color);
}

void Player::Draw(SpriteData sd, COLOR_ARGB color)
{
	//_bound->Draw(sd,color);
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

float Player::GetScale()
{
	return playerImage.getScale();
}
D3DXVECTOR3 Player::GetCenter()
{
	return D3DXVECTOR3(playerImage.getCenterX(),playerImage.getCenterY(), _position.z);
}

void Player::DBounce(D3DXVECTOR3 distance)
{
	_position+=distance;
	
	if(distance.x != 0)
		_velocity.x=0;

	if(distance.y!=0)
		_velocity.y=0;
}

void Player::VBounce(D3DXVECTOR3 velocity)
{
	_velocity+=velocity;
}

D3DXVECTOR3 Player::GetDirection()
{
	float degrees = playerImage.getDegrees();
	if(playerImage.isFlippedHorizontal())
	{
		//look left
		if(degrees==45)
		{
			return D3DXVECTOR3(-1,-1,0);
		}
		else if(degrees==0)
		{
			return D3DXVECTOR3(-1,0,0);
		}
		else
		{
			return D3DXVECTOR3(-1,1,0);
		}
	}
	else
	{
		//look right
		if(degrees==45)
		{
			return D3DXVECTOR3(1,1,0);
		}
		else if(degrees==0)
		{
			return D3DXVECTOR3(1,0,0);
		}
		else
		{
			return D3DXVECTOR3(1,-1,0);
		}
	}
}