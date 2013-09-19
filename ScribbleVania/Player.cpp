#include "Player.h"

Player::Player() : GameObject()
{
	type = ObjectType::Player;
}

Player::Player(unsigned int id) : GameObject(id)
{
	type = ObjectType::Player;
}

Player::~Player()
{
	_game=NULL; 
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
	}
	return true;
}

void Player::Shutdown()
{
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
	input=NULL;
}

void Player::Draw(COLOR_ARGB color)
{
	playerImage.draw(color);
}

void Player::Draw(SpriteData sd, COLOR_ARGB color)
{
	playerImage.draw(sd,color);
}

void Player::Reset()
{
	playerTexture.onResetDevice();
}