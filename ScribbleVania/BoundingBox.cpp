#include "BoundingBox.h"
#include "ObjectManager.h"
#include "constants.h"
#include "BoundingCircle.h"

BoundingBox::BoundingBox(unsigned int ownerID, GameObject* ownerObject)
{
	_owner=ownerObject;
	_type = CollidableType::Box;
}

BoundingBox::~BoundingBox()
{
	_owner=NULL;
}

void BoundingBox::Update(float elapsedTime)
{
	_image.setX(_owner->getX());
	_image.setY(_owner->getY());
}

void BoundingBox::Draw(SpriteData sd, COLOR_ARGB color)
{
	_image.draw(sd,color);
}

void BoundingBox::Draw(COLOR_ARGB color)
{
	_image.draw(color);
}

bool BoundingBox::Initialize(Game* game, int height, int width)
{
	_height = height;
	_width = width;
	if(!_texture.initialize(game->getGraphics(), BOX_IMAGE))
	{
		return false;
	}
	else
	{
		if(!_image.initialize(game->getGraphics(),width, height,0,&_texture))
		{
			return false;
		}
	}
	_image.setX(_owner->getX());
	_image.setY(_owner->getY());
	return true;
}

float BoundingBox::Top()
{
	return _owner->getY();
}

float BoundingBox::Bottom()
{
	return _owner->getY() + _height;
}

float BoundingBox::Left()
{
	return _owner->getX();
}

float BoundingBox::Right()
{
	return _owner->getX() + _width;
}

void BoundingBox::Reset()
{
	_texture.onResetDevice();
}

void BoundingBox::Shutdown()
{
	_texture.onLostDevice();
}

Position BoundingBox::GetCenter()
{
	Position temp;
	temp.x = _image.getCenterX();
	temp.y = _image.getCenterY();
	return temp;
}

bool BoundingBox::Intersects(Collidable* c)
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

bool BoundingBox::IntersectB(BoundingBox* b)
{
	bool outBot = this->Bottom() < b->Top();
	bool outTop = this->Top() > b->Bottom();
	bool outLeft = this->Left() > b->Right();
	bool outRight = this->Right() < b->Left();
	return !(outBot || outTop || outLeft|| outRight);
}

bool BoundingBox::IntersectC(BoundingCircle* c)
{
	float closestX;
	float closestY;

	if(c->GetCenter().x < this->Left())
	{
		closestX = this->Left();
	}
	else if (c->GetCenter().x > this->Right())
	{
		closestX = this->Right();
	}
	else
	{
		closestX = c->GetCenter().x;
	}

	if(c->GetCenter().y < this->Top())
	{
		closestY = this->Top();
	}
	else if(c->GetCenter().y > this->Bottom())
	{
		closestY = this->Bottom();
	}
	else
	{
		closestY = c->GetCenter().y;
	}

	float distanceX = c->GetCenter().x - closestX;
	float distanceY = c->GetCenter().y - closestY;

	float distanceSqr = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSqr < (c->Radius() * c->Radius());
}
