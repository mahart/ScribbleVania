#include "../../Header/Collidable/BoundingBox.h"
#include "../../Header/ObjectManager.h"
#include "../../Header/Constants.h"
#include "../../Header/Collidable/BoundingCircle.h"
#include "../../Header/ObjectManager.h"

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
	D3DXVECTOR3 p = _owner->GetPosition();
	
	_image.setX(p.x);
	_image.setY(p.y);
}

void BoundingBox::Draw(SpriteData sd, COLOR_ARGB color)
{
	_image.draw(sd,color);
}

void BoundingBox::Draw(COLOR_ARGB color)
{
	_image.draw(color);
}

bool BoundingBox::Initialize(ObjectManager* om, int height, int width)
{
	_height = height;
	_width = width;
	D3DXVECTOR3 p;
	if(!_texture.initialize(om->GetGraphics(), BOX_IMAGE))
	{
		return false;
	}
	else
	{
		if(!_image.initialize(om->GetGraphics(),width, height,0,&_texture))
		{
			return false;
		}
	}
	p = _owner->GetPosition();
	_image.setX(p.x);
	_image.setY(p.y);
	return true;
}

float BoundingBox::Top()
{
	return _owner->GetPosition().y;
}

float BoundingBox::Bottom()
{
	return _owner->GetPosition().y + _height;
}

float BoundingBox::Left()
{
	return _owner->GetPosition().x;
}

float BoundingBox::Right()
{
	return _owner->GetPosition().x + _width;
}

void BoundingBox::Reset()
{
	_texture.onResetDevice();
}

void BoundingBox::Shutdown()
{
	_texture.onLostDevice();
}

D3DXVECTOR3 BoundingBox::GetCenter()
{
	D3DXVECTOR3 temp;
	temp.x = _image.getCenterX();
	temp.y = _image.getCenterY();
	temp.z = _owner->GetPosition().z;
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

D3DXVECTOR3 BoundingBox::GetNearestPoint(D3DXVECTOR3 center)
{
	D3DXVECTOR3 pt;

	if(this->Top()>center.y)
	{
		pt.y=this->Top();
	}
	else if (this->Bottom() < center.y)
	{
		pt.y=this->Bottom();
	}
	else
	{
		pt.y=center.y;
	}

	if(this->Left()> center.x)
	{
		pt.x = this->Left();
	}
	else if(this->Right()< center.x)
	{
		pt.x = this->Right();
	}
	else
	{
		pt.x = center.x;
	}
	return pt;
}