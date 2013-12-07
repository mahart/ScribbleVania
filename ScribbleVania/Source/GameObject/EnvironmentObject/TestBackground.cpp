#include "../../../Header/GameObject/EnvironmentObject/TestBackGround.h"
#include "../../../Header/ObjectManager.h"

TestBackGround::TestBackGround() : EnvironmentObject()
{
	this->_type = ObjectType::Background;
	_position.z = -1;
	_static=true;
}

TestBackGround::TestBackGround(unsigned int ID) : EnvironmentObject(ID)
{
	this->_type = ObjectType::Background;
	_position.z=-1;
	_static=true;
}

TestBackGround::~TestBackGround()
{
	EnvironmentObject::~EnvironmentObject();
}

bool TestBackGround::Initialize(ObjectManager* om)
{
	return TestBackGround::Initialize(om,ZERO_VECTOR);
}


bool TestBackGround::Initialize(ObjectManager* om, D3DXVECTOR3 position)
{
	_om=om;
	
	if(!objectTexture.initialize(_om->GetGraphics(),TEST_BG_2))
	{
		return false;
	}
	else
	{
		float xScale = (float)GAME_WIDTH/objectTexture.getWidth();
		float yScale = (float)GAME_HEIGHT/objectTexture.getHeight();
		float scale = (xScale+yScale)/2;
		if(! objectImage.initialize(_om->GetGraphics(),0, 0,0,&objectTexture,yScale))
		{
			return false;
		}
		_position.x = 0;
		_position.y = 0;
	}
	return true;
}

void TestBackGround::Update(float elapsedTime)
{
	objectImage.setX(_position.x);
	objectImage.setY(_position.y);
}



