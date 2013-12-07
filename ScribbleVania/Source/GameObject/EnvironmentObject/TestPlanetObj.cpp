#include "../../../Header/GameObject/EnvironmentObject/TestPlanetObj.h"
#include "../../../Header/Collidable/BoundingCircle.h"
#include "../../../Header/ObjectManager.h"

TestPlanetObj::TestPlanetObj() : EnvironmentObject()
{
	_velocity= ZERO_VECTOR;
	
	_type = ObjectType::EnvironmentObject;
	_static=true;
	_position.z=1;
	_bound = new BoundingCircle(0, this);
}

TestPlanetObj::TestPlanetObj(unsigned int ID) : EnvironmentObject(ID)
{
	_velocity= ZERO_VECTOR;
	_type = ObjectType::EnvironmentObject;
	_static=true;
	_position.z=1;
	_bound = new BoundingCircle(ID, this);
}

TestPlanetObj::~TestPlanetObj()
{
	SAFE_DELETE(_bound);
	_bound=NULL;
	EnvironmentObject::~EnvironmentObject();
}

bool TestPlanetObj::Initialize(ObjectManager* om)
{
	return TestPlanetObj::Initialize(om, D3DXVECTOR3(GAME_WIDTH*0.5f - objectImage.getWidth() *0.5f, 
			 GAME_HEIGHT*0.5f - objectImage.getHeight()*0.5f, 1));
}

bool TestPlanetObj::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	if(_position == ZERO_VECTOR)
		_position = position;

	if(!objectTexture.initialize(_om->GetGraphics(),PLANET_IMAGE))
	{
		return false;
	}
	else
	{
		if(!objectImage.initialize(_om->GetGraphics(),0, 0,0,&objectTexture))
		{
			return false;
		}
		_position = position;
		int rad=0;
		if(this->GetWidth()>this->GetHeight())
		{
			rad = this->GetWidth()/2;
		}
		else
		{
			rad = this ->GetHeight()/2;
		}
		
		if(!_bound->Initialize(_om,rad,-1))
		{
			return false;
		}
	}
	objectImage.setX(this->_position.x);
	objectImage.setY(this->_position.y);
	return true;
}

void TestPlanetObj::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
	_bound->Update(elapsedTime);
}

void TestPlanetObj::Draw(SpriteData sd, COLOR_ARGB color)
{
	_bound->Draw(sd,color);
	EnvironmentObject::Draw(sd,color);
}

void TestPlanetObj::Draw(COLOR_ARGB color)
{
	_bound->Draw(color);
	EnvironmentObject::Draw(color);
}