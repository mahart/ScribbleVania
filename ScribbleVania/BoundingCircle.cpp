#include "BoundingCircle.h"
#include "GameObject.h"
#include "BoundingBox.h"

BoundingCircle::BoundingCircle(unsigned int ownerId, GameObject* ownerObject)
{
	_owner = ownerObject;
	_type = CollidableType::Circle;
}

BoundingCircle::~BoundingCircle()
{
	_owner = NULL;
}

bool BoundingCircle::Initialize(Game* game, int radius, int UNUSED)
{
	_radius=radius;
	if(!_texture.initialize(game->getGraphics(), CIRCLE_IMAGE))
	{
		return false;
	}
	else
	{
		if(!_image.initialize(game->getGraphics(),64,64,0,&_texture))
		{
			return false;
		}
	}
	float scale = (float)radius/32;
	_image.setScale(scale);
	_image.setX(_owner->getX());
	_image.setY(_owner->getY());
	
	return true;
}

void BoundingCircle::Update(float elapsedTime)
{
	_image.setX(_owner->getX());
	_image.setY(_owner->getY());
}

void BoundingCircle::Draw(SpriteData sd, COLOR_ARGB color )
{
	_image.draw(sd,color);
}

void BoundingCircle::Draw(COLOR_ARGB color)
{
	_image.draw(color);
}

float BoundingCircle::Radius()
{
	return (float)_radius;
}

void BoundingCircle::Reset()
{
	_texture.onResetDevice();
}

void BoundingCircle::Shutdown()
{
	_texture.onLostDevice();
}

Position BoundingCircle::GetCenter()
{
	Position temp;
	temp.x = _image.getCenterX();
	temp.y = _image.getCenterY();
	return temp;
}

bool BoundingCircle::Intersects(Collidable* c)
{
	switch(c->Type())
	{
		case CollidableType::Box:
			return IntersectB((BoundingBox*) c);
		case CollidableType::Circle:
			return IntersectC((BoundingCircle*) c);
		default:
			return false;
	}
}

bool BoundingCircle::IntersectC(BoundingCircle* c)
{
	float distX = this->GetCenter().x - c->GetCenter().x;
	float distY = this->GetCenter().y - c->GetCenter().y;
	float sqrDist = (distX*distX) + (distY*distY);
	return sqrDist < ((this->Radius() + c->Radius()) * (this->Radius() + c->Radius()));
}

bool BoundingCircle::IntersectB(BoundingBox* b)
{
	float closestX;
	float closestY;

	if(this->GetCenter().x < b->Left())
	{
		closestX = b->Left();
	}
	else if (this->GetCenter().x > b->Right())
	{
		closestX = b->Right();
	}
	else
	{
		closestX = this->GetCenter().x;
	}

	if(this->GetCenter().y < b->Top())
	{
		closestY = b->Top();
	}
	else if(this->GetCenter().y > b->Bottom())
	{
		closestY = b->Bottom();
	}
	else
	{
		closestY = this->GetCenter().y;
	}

	float distanceX =  this->GetCenter().x -closestX;
	float distanceY = this->GetCenter().y - closestY;

	float distanceSqr = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSqr < (this->Radius() * this->Radius());
}
