#include "../../../Header/GameObject/EnvironmentObject/Door.h"
#include "../../../Header/Collidable/BoundingBox.h"
#include "../../../Header/GameObject/Player/Player.h"
Door::Door()
{
	_velocity = ZERO_VECTOR;
	_type = ObjectType::EnvironmentObject;
	_subType = EnvSubType::Door;
	_static=true;
	_bound = new BoundingBox(0, this);
	_height = 0;
	_width = 0;
	_room=NULL;
}

Door::Door(unsigned int ID, int height, int width, D3DXVECTOR3 position, D3DXVECTOR3 exit, Room** room)
{
	_velocity = ZERO_VECTOR;
	_id = ID;
	_type = ObjectType::EnvironmentObject;
	_subType = EnvSubType::Door;
	_static=true;
	_position=position;
	_bound = new BoundingBox(ID, this);
	_height = height;
	_width = width;
	_room = room;
	_open=false;
	_exit = exit;
}

Door::~Door()
{
	SAFE_DELETE(_bound);
	SAFE_DELETE(_room);
	_room=NULL;
	_bound=NULL;
	EnvironmentObject::~EnvironmentObject();
}
Room* Door::GetRoom()
{
	return *_room;
}

D3DXVECTOR3 Door::GetExit()
{
	return _exit;
}

bool Door::Initialize(ObjectManager* om)
{
	return Door::Initialize(om,ZERO_VECTOR);
}

bool Door::Initialize(ObjectManager* om, D3DXVECTOR3 position)
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

bool Door::SwitchOpenClose()
{
	this->Shutdown();
	if(!_open)
	{
		_open = true;
		if(!objectTexture.initialize(_om->GetGraphics(), OPEN_DOOR_IMAGE))
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
		
	}
	else
	{
		_open = false;
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
	}

	return true;
}

void Door::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
	_bound->Update(elapsedTime);
}

void Door::Draw(COLOR_ARGB color)
{
	//_bound->Draw(color);
	EnvironmentObject::Draw(color);
}

void Door::Draw(SpriteData sd, COLOR_ARGB color)
{
	//_bound->Draw(sd,color);
	EnvironmentObject::Draw(sd,color);
}

void Door::ProcessCollision(GameObject* obj)
{
	if(!(obj->GetObjectType() == ObjectType::Projectile && obj->GetOwnerID()==0 &&!_open))
	{
		return;
	}
	/*Player* p = (Player*)obj;

	if(!this->_open)
	{
		if(this->_position.x < p->GetPosition().x)
			p->DBounce(D3DXVECTOR3(5,0,0));
		else
			p->DBounce(D3DXVECTOR3(-5,0,0));

		if(this->_position.y < p->GetPosition().y)
			p->DBounce(D3DXVECTOR3(0,5,0));
		else
			p->DBounce(D3DXVECTOR3(0,-5,0));
	}*/
	this->SwitchOpenClose();
}