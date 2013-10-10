#include "Player.h"

Player::Player() : GameObject()
{
	_position.depth=0;
	_type = ObjectType::Player;
	_bound = new BoundingBox(0, this);
}

Player::Player(unsigned int id) : GameObject(id)
{
	_position.depth=0;
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
	_game = game;
	_position.x=0;
	_position.y=0;
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
	if(input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
    {
        _position.x = _position.x + elapsedTime * SHIP_SPEED;
        if (_position.x > GAME_WIDTH)               // if off screen right
            _position.x = (float)-playerImage.getWidth();     // position off screen left
    }
    if(input->isKeyDown(SHIP_LEFT_KEY))             // if move left
    {
        _position.x = _position.x - elapsedTime * SHIP_SPEED;
        if (_position.x < -playerImage.getWidth())         // if off screen left
            _position.x = (float)GAME_WIDTH;           // position off screen right
    }
    if(input->isKeyDown(SHIP_UP_KEY))               // if move up
    {
        _position.y = _position.y - elapsedTime * SHIP_SPEED;
        if (_position.y < -playerImage.getHeight())        // if off screen top
            _position.y = (float)GAME_HEIGHT;          // position off screen bottom
    }
    if(input->isKeyDown(SHIP_DOWN_KEY))             // if move down
    {
        _position.y = _position.y + elapsedTime * SHIP_SPEED;
        if (_position.y> GAME_HEIGHT)              // if off screen bottom
            _position.y = (float)-playerImage.getHeight();    // position off screen top
    }
	playerImage.setX(_position.x);
	playerImage.setY(_position.y);
    playerImage.update(elapsedTime);
	_bound->Update(elapsedTime);
	input=NULL;
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

Position Player::GetCenter()
{
	Position temp;
	temp.x = playerImage.getCenterX();
	temp.y = playerImage.getCenterY();
	return temp;
}