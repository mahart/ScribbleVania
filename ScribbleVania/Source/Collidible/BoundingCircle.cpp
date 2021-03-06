#include "../../Header/Collidable/BoundingCircle.h"
#include "../../Header/GameObject/GameObject.h"
#include "../../Header/Collidable/BoundingBox.h"
#include "../../Header/ObjectManager.h"

BoundingCircle::BoundingCircle(unsigned int ownerId, GameObject* ownerObject)
{
	_owner = ownerObject;
	_type = CollidableType::Circle;
}

BoundingCircle::~BoundingCircle()
{
	_owner = NULL;
}

bool BoundingCircle::Initialize(ObjectManager* om, int radius, int UNUSED)
{
	D3DXVECTOR3 p;
	float scale;
	if(!_texture.initialize(om->GetGraphics(), CIRCLE_IMAGE))
	{
		return false;
	}
	else
	{
		float xScale = (_owner->GetWidth()*_owner->GetScale())/64;
		float yScale = (_owner->GetHeight()*_owner->GetScale())/64;
		scale = (xScale+yScale)/2;
		if(!_image.initialize(om->GetGraphics(),64,64,0,&_texture, scale))
		{
			return false;
		}
	}
	_radius=radius;
	p=_owner->GetPosition();
	_image.setX(p.x);
	_image.setY(p.y);
	
	return true;
}

void BoundingCircle::Update(float elapsedTime)
{
	D3DXVECTOR3 p = _owner->GetPosition();
	_image.setX(p.x);
	_image.setY(p.y);
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

D3DXVECTOR3 BoundingCircle::GetCenter()
{
	D3DXVECTOR3 temp;
	temp.x = _image.getCenterX();
	temp.y = _image.getCenterY();
	temp.z = _owner->GetPosition().z;
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
	float dist2 = distX*distX + distY*distY;
	float r2= (this->Radius() + c->Radius())*(this->Radius() + c->Radius());
	return dist2 <= r2;//((this->Radius() + c->Radius()) * (this->Radius() + c->Radius()));
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
	float rSqr = this->Radius() * this->Radius();
	return distanceSqr <= (this->Radius() * this->Radius());
}

D3DXVECTOR3 BoundingCircle::GetNearestPoint(D3DXVECTOR3 center)
{
	D3DXVECTOR3 diff = center- this->GetCenter();
	diff.z=0;
	D3DXVECTOR3 pt;
	D3DXVec3Normalize(&pt, &diff);

	pt = pt*(float)_radius;

	if( center.x < this->GetCenter().x)
	{
		if(pt.x <center.x)
			pt.x=center.x;
	}
	else if (center.x >this->GetCenter().x)
	{
		if(pt.x > center.x)
			pt.x=center.x;
	}

	if(center.y <this->GetCenter().y)
	{
		if(pt.y < center.y)
			pt.y=center.y;
	}
	else if (center.y >this->GetCenter().y )
	{
		if(pt.y >center.y)
			pt.y=center.y;
	}
	return pt;
}