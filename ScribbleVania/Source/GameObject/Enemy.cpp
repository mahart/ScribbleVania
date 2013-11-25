#include "../../Header/GameObject/Enemy.h"

Enemy::Enemy()
{
	_type = ObjectType::Enemy;
}

Enemy::Enemy(unsigned int ID) : GameObject(ID)
{
	_type = ObjectType::Enemy;
}

Enemy::~Enemy()
{
	_game = NULL;
	this->Shutdown();
}

bool Enemy::Initialize(Game* game)
{
	return Enemy::Initialize(game, ZERO_VECTOR);
}

bool Enemy::Initialize(Game* game, D3DXVECTOR3 position)
{
	_game=game;
	return true;
}

void Enemy::Shutdown()
{
	objectTexture.onLostDevice();
	if(_bound!=NULL)
		_bound->Shutdown();
}

void Enemy::Reset()
{
	objectTexture.onResetDevice();
	if(_bound!=NULL)
		_bound->Reset();

}

void Enemy::Draw(COLOR_ARGB color)
{
	objectImage.draw(color);
}

void Enemy::Draw(SpriteData sd, COLOR_ARGB color)
{
	objectImage.draw(sd,color);
}

D3DXVECTOR3 Enemy::GetCenter()
{
	return D3DXVECTOR3(objectImage.getCenterX(),objectImage.getCenterY(),this->_position.z);
}

int Enemy::GetWidth()
{
	return objectImage.getWidth();
}

int Enemy::GetHeight()
{
	return objectImage.getWidth();
}