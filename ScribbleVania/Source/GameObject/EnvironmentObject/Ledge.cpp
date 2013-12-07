#include "../../../Header/GameObject/EnvironmentObject/Ledge.h"
#include "../../../Header/Collidable/BoundingBox.h"
#include "../../../Header/ObjectManager.h"

Ledge::Ledge()
{
	_velocity = ZERO_VECTOR;
	_type = ObjectType::EnvironmentObject;
	_subType = EnvSubType::Ledge;
	_static=true;
	_bound = new BoundingBox(0, this);
	_height = 0;
	_width = 0;
}

Ledge::Ledge(unsigned int ID, int height, int width, D3DXVECTOR3 position)
{
	_velocity = ZERO_VECTOR;
	_id = ID;
	_type = ObjectType::EnvironmentObject;
	_subType = EnvSubType::Ledge;
	_static=true;
	_position=position;
	_bound = new BoundingBox(ID, this);
	_height = height;
	_width = width;
}

Ledge::~Ledge()
{
	SAFE_DELETE(_bound);
	_bound=NULL;
	EnvironmentObject::~EnvironmentObject();
}

bool Ledge::Initialize(ObjectManager* om)
{
	return Ledge::Initialize(om, ZERO_VECTOR);
}

bool Ledge::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om = om;

	if(_position == ZERO_VECTOR)
		_position = position;

	if(!objectTexture.initialize(_om->GetGraphics(), LEDGE_IMAGE))
	{
		return false;
	}
	else
	{
		if(!objectImage.initialize(_om->GetGraphics(), _height, _width,0,&objectTexture))
		{
			return false;
		}
		if(!_bound->Initialize(_om, objectImage.getHeight(), objectImage.getWidth()))
		{
			return false;
		}
	}
	return true;
}

void Ledge::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
	_bound->Update(elapsedTime);
}

void Ledge::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	EnvironmentObject::Draw(color);
}



void Ledge::Draw(SpriteData sd, COLOR_ARGB color)
{
	//_bound->Draw(sd,color);
	EnvironmentObject::Draw(sd,color);
}