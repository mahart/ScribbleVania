#include "../../Header/GameObject/ObjectFactory.h"
#include "../../Header/Room/Room.h"
#include "../../Header/ObjectManager.h"
#include "../../Header/GameObject/EnvironmentObject/Door.h"
#include "../../Header/GameObject/EnvironmentObject/Ledge.h"
#include "../../Header/GameObject/EnvironmentObject/TestBackground.h"
#include "../../Header//GameObject/EnvironmentObject/TestBarrier.h"
#include "../../Header/GameObject/EnvironmentObject/TestPlanetObj.h"
#include "../../Header/GameObject//Enemy/RedSnailEnemy.h"
#include "../../Header/GameObject/Enemy/GraySnailEnemy.h"
#include "../../Header/GameObject/Boss/SnailBoss.h"
#include "../../Header/GameObject/Enemy/FatFrogEnemy.h"
#include "../../Header/GameObject/Enemy/BombFrogEnemy.h"
#include "../../Header/GameObject/Boss/FrogBoss.h"

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

Room* ObjectFactory::MakeS1()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));

	//Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//Ceiling
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, 0,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));

	//Right Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.9f)-30.0f, 0), &_om->Snail2));

	return new Room(temp);
}


Room* ObjectFactory::MakeS2()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));

	//Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//Ceiling
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, 0,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));

	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.9f-50, 2), D3DXVECTOR3(GAME_WIDTH-60, (GAME_HEIGHT*0.9f)-30.0f,0), &_om->Snail1));

	//Right Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2),D3DXVECTOR3(0, GAME_HEIGHT*0.25f-50, 2), &_om->Snail3));

	//Floor Over Door
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH*0.2f,D3DXVECTOR3(GAME_WIDTH*0.8f, GAME_HEIGHT*0.9f-100,1),EnvSubType::Floor));
	
	//Door over Floor
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-150,2),D3DXVECTOR3(0, GAME_HEIGHT*0.25f-50, 2), &_om->Frog1));

	id = _om->GetNextID();
	temp->push_back( new Ledge(id,5, 24,
		D3DXVECTOR3(GAME_WIDTH*0.8f-1, (GAME_HEIGHT*0.9f-100)+1,3)));

	return new Room(temp);
}

Room* ObjectFactory::MakeS3()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));

	//Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//Ceiling
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, 0,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));

	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.25f-50, 2), D3DXVECTOR3(GAME_WIDTH-60, (GAME_HEIGHT*0.9)-50.0f,0), &_om->Snail2));

	//Right Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.5f)-50.0f, 0), &_om->Snail4));

	//Upper Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH*0.85f,D3DXVECTOR3(0,GAME_HEIGHT*0.25f,1),EnvSubType::Floor));

	id = _om->GetNextID();
	temp->push_back( new Ledge(id,5, 24,
		D3DXVECTOR3(GAME_WIDTH*0.85f-4, GAME_HEIGHT*0.25f+1,3)));

	//Upper Middle Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH*0.85f,D3DXVECTOR3(GAME_WIDTH*0.15f,GAME_HEIGHT*0.45f,1),EnvSubType::Floor));

	id = _om->GetNextID();
	temp->push_back( new Ledge(id,5, 24,
		D3DXVECTOR3(GAME_WIDTH*0.15f-1, GAME_HEIGHT*0.45f,3)));

	/*//Lower Middle Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH*0.85f,D3DXVECTOR3(0,GAME_HEIGHT*0.65f,1),EnvSubType::Floor));
	*/
	//Lower Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH*0.85f,D3DXVECTOR3(GAME_WIDTH*0.15f,GAME_HEIGHT*0.9f-75,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,(GAME_HEIGHT*0.9f-75)-(GAME_HEIGHT*0.45f), 25,D3DXVECTOR3(GAME_WIDTH*0.15f, GAME_HEIGHT*0.45f+25,1),EnvSubType::Wall));

	return new Room(temp);
}

Room* ObjectFactory::MakeS4()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));

	//Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.5f, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.5f,1),EnvSubType::Floor));

	//Ceiling
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, 0,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));
	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.5f-50, 2), D3DXVECTOR3(GAME_WIDTH-60, (GAME_HEIGHT*0.9f)-30.0f,0), &_om->Snail3));
	//Right Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.5f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.9f)-30.0f, 0), &_om->SnailB));

	return new Room(temp);
}

Room* ObjectFactory::MakeSB()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));

	//Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//Ceiling
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT*0.1f, GAME_WIDTH,D3DXVECTOR3(0, 0,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));
	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.9f-50, 2), D3DXVECTOR3(GAME_WIDTH-60, (GAME_HEIGHT*0.5f)-50.0f,0), &_om->Snail4));
	//Right Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

		
	//SnailBoss
	id = _om->GetNextID();
	temp->push_back(new SnailBoss(id,(Player*)_om->GetObjectByID(0)));
	return new Room(temp);
}


Room* ObjectFactory::MakeTestRoom1()
{
	vector<GameObject*> * temp = new vector<GameObject*>();
	unsigned int id = _om->GetNextID();
	//temp->push_back(new TestPlanetObj(id));
	
	//id = _om->GetNextID();
	temp->push_back(new TestBackGround(id));
	
	//Floor
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),EnvSubType::Floor));

	//Ceiling
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,25, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.2f,1),EnvSubType::Floor));

	//Left Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),EnvSubType::Wall));

	//Left Door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.9f-50, 2), D3DXVECTOR3(GAME_WIDTH-60, (GAME_HEIGHT*0.9f)-50.0f,0), &_om->room3));

	//Right Wall
	id = _om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.9f)-50.0f, 0), &_om->room2));

	

	//Gray Snail
	id = _om->GetNextID();
	temp->push_back(new GraySnailEnemy(id, D3DXVECTOR3(GAME_WIDTH/2, GAME_HEIGHT*0.9f-50, 2), (Player*) _om->GetObjectByID(0)));

	/*
	//Fat Frog
	id = _om->GetNextID();
	temp->push_back(new FrogBoss(id,(Player*)_om->GetObjectByID(0),D3DXVECTOR3(GAME_WIDTH/2+75, GAME_HEIGHT/2,2)));

	id = _om->GetNextID();
	temp->push_back(new BombFrogEnemy(id, D3DXVECTOR3(GAME_WIDTH/2+75, GAME_HEIGHT/2,0),(Player*)_om->GetObjectByID(0)));

	id = _om->GetNextID();
	temp->push_back(new FatFrogEnemy(id, D3DXVECTOR3(GAME_WIDTH/2+75, GAME_HEIGHT/2,0),(Player*)_om->GetObjectByID(0)));
	*/
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
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(0, GAME_HEIGHT*0.9f-50, 2), D3DXVECTOR3(GAME_WIDTH-60,  (GAME_HEIGHT*0.9f)-50.0f,0), &_om->room1));

	//right wall
	id=_om->GetNextID();
	temp->push_back(new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),EnvSubType::Wall));

	//right door
	id = _om->GetNextID();
	temp->push_back(new Door(id, 26,50, D3DXVECTOR3(GAME_WIDTH-26, GAME_HEIGHT*0.9f-50,2), D3DXVECTOR3(30,  (GAME_HEIGHT*0.9f)-50.0f, 0), &_om->room3));

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

	//RedSnail 1
	id = _om->GetNextID();
	temp->push_back(new RedSnailEnemy(id, D3DXVECTOR3(GAME_WIDTH-150, GAME_HEIGHT*0.9f-50, 2),
		(Player*)_om->GetObjectByID(0)));

	//RedSnail 2
	id = _om->GetNextID();
	temp->push_back(new RedSnailEnemy(id, D3DXVECTOR3(GAME_WIDTH/2, GAME_HEIGHT*0.9f-50, 2),
		(Player*)_om->GetObjectByID(0)));

	//RedSnail 3
	id = _om->GetNextID();
	temp->push_back(new RedSnailEnemy(id, D3DXVECTOR3(GAME_WIDTH/3, GAME_HEIGHT*0.9f-50, 2),
		(Player*)_om->GetObjectByID(0)));

	//Gray Snail
	id = _om->GetNextID();
	temp->push_back(new GraySnailEnemy(id, D3DXVECTOR3(GAME_WIDTH/2, GAME_HEIGHT*0.9f-50, 2), (Player*) _om->GetObjectByID(0)));

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