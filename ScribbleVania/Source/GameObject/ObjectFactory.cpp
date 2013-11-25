#include "../../Header/GameObject/ObjectFactory.h"
#include "../../Header/Room/Room.h"
#include "../../Header/ObjectManager.h"
#include "../../Header/GameObject/EnvironmentObject/Door.h"
#include "../../Header/GameObject/EnvironmentObject/Ledge.h"
#include "../../Header/GameObject/EnvironmentObject/TestBackground.h"
#include "../../Header//GameObject/EnvironmentObject/TestBarrier.h"
#include "../../Header/GameObject/EnvironmentObject/TestPlanetObj.h"
#include "../../Header/GameObject//Enemy/SnailEnemy.h"
ObjectFactory::ObjectFactory()
{
}

ObjectFactory::ObjectFactory(ObjectManager* om)
{
	_om=om;
}

ObjectFactory::~ObjectFactory()
{
}

Room* ObjectFactory::MakeTestRoom1()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	temp->push_back(new TestPlanetObj(id));
	
	id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));
	
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));

	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.9f-50, 2), D3DXVECTOR3(GAME_WIDTH-60, (GAME_HEIGHT*0.9f)-30.0f,0), &_om->room3));

	//Right Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.9f)-30.0f, 0), &_om->room2));

	return new Room(temp);
}

Room* ObjectFactory::MakeTestRoom2()
{
	unsigned int id = _om->GetNextID();
	int platformWidth = GAME_WIDTH/3;
	int platformHeight = 25;
	float platformX = GAME_WIDTH/3.0f;
	float platformY = GAME_HEIGHT*0.7f;
	float platformZ = 1.0f;
	vector<GameObject*> * temp = new vector<GameObject*>();

	temp->push_back(new TestBackGround(id));
	
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));
	
	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.9f-50, 2), D3DXVECTOR3(GAME_WIDTH-60,  (GAME_HEIGHT*0.9f)-30.0f,0), &_om->room1));

	//right wall
	id=_om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.9f)-30.0f, 0), &_om->room3));

	//Platform
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id, platformHeight, platformWidth, 
		D3DXVECTOR3(platformX,platformY,platformZ), EnvSubType::Floor));

	//Left Platform Ledge
	id = _om->GetNextID();
	temp->push_back( new Ledge(id,5, platformHeight-1,
		D3DXVECTOR3(platformX-1, platformY+1,platformZ+1)));

	//Right platform ledge
	id = _om->GetNextID();
	temp->push_back(new Ledge(id, 5, platformHeight-1,
		D3DXVECTOR3(platformX + platformWidth -4, platformY+1, platformZ+1)));

	//left platform wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id, GAME_HEIGHT*0.9-platformY, 25,
		D3DXVECTOR3(platformX,platformY+25,1),EnvSubType::Wall));

	//right platform wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id, GAME_HEIGHT*0.9-platformY, 25,
		D3DXVECTOR3(platformX +platformWidth - 25, platformY+25,1),EnvSubType::Wall));

	//Snail
	id = _om->GetNextID();
	temp->push_back(new SnailEnemy(id, D3DXVECTOR3(GAME_WIDTH-150, GAME_HEIGHT*0.9f-50, 2)));
	return new Room(temp);
}

Room* ObjectFactory::MakeTestRoom3()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));

	//Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//RightWall
	id = _om->GetNextID();
	temp->push_back( new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));
	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.9f)-30.0f, 0), &_om->room1));


	//LeftWall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));
	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.9f-50, 2), D3DXVECTOR3(GAME_WIDTH-60,  (GAME_HEIGHT*0.9f)-30.0f,0), &_om->room2));

	//T
	id = _om->GetNextID();
	temp->push_back( new TestBarrier(id,200, 25,D3DXVECTOR3(300, GAME_HEIGHT*0.9f-200,1),EnvSubType::Other));
	
	id = _om->GetNextID();
	temp->push_back( new TestBarrier(id,25, 75,D3DXVECTOR3(275, GAME_HEIGHT*0.9f-225,1),EnvSubType::Other));
	//END T

	
	//E
	id = _om->GetNextID();
	temp->push_back( new TestBarrier(id,200, 25,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-200,1),EnvSubType::Other));

	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 75,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-225,1),EnvSubType::Other));

	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 75,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-100,1),EnvSubType::Other));

	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 75,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-25,1),EnvSubType::Other));
	//END E

	//S
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 75,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-125,1),EnvSubType::Other));
	
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 25,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-100,1),EnvSubType::Other));

	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 75,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-75,1),EnvSubType::Other));

	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 25,D3DXVECTOR3(600, GAME_HEIGHT*0.9f-50,1),EnvSubType::Other));

	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 75,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-25,1),EnvSubType::Other));
	//END S 

	//T
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,100, 25,D3DXVECTOR3(700, GAME_HEIGHT*0.9f-100,1),EnvSubType::Other));
	
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, 75,D3DXVECTOR3(675, GAME_HEIGHT*0.9f-125,1),EnvSubType::Other));
	//END T
	
	return new Room(temp);
}