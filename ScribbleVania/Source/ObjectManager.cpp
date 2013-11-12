#include "../Header/ObjectManager.h"
#include "../Header/GameObject/Player/Player.h"
#include "../Header/GameObject/EnvironmentObject/TestPlanetObj.h"
#include "../Header/GameObject/EnvironmentObject/TestBackground.h"
#include "../Header/GameObject/EnvironmentObject/TestBarrier.h"

static void FakeFactory(unordered_map<unsigned int,GameObject*>* objects, ObjectManager* om, DepthTreeNode* drawTree)
{
	unsigned int id = om->GetNextID();
	objects->insert(std::make_pair(id,new TestPlanetObj(id)));
	if(drawTree == NULL)
	{
		drawTree = new DepthTreeNode(om->GetObjectByID(id)->GetPosition().z ,id);
	}
	else
	{
		drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);
	}

	id = om->GetNextID();
	objects->insert(std::make_pair(id, new TestBackGround(id)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	//FLOOR
	objects->insert(std::make_pair(id, new TestBarrier(id,25, GAME_WIDTH,D3DXVECTOR3(0, GAME_HEIGHT*0.9f,1),ObjectType::FloorEnvironment)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);
	
	//LEFT WALL
	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(GAME_WIDTH-25, 0,1),ObjectType::WallEnvironment)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);
	//RIGHT WALL
	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,GAME_HEIGHT, 25,D3DXVECTOR3(0, 0,1),ObjectType::WallEnvironment)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	//T
	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,200, 25,D3DXVECTOR3(300, GAME_HEIGHT*0.9f-200,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(275, GAME_HEIGHT*0.9f-225,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);
	//END T

	//E
	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,200, 25,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-200,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-225,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-100,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(400, GAME_HEIGHT*0.9f-25,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);
	//END E

	//S

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-125,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 25,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-100,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-75,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 25,D3DXVECTOR3(600, GAME_HEIGHT*0.9f-50,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(550, GAME_HEIGHT*0.9f-25,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);
	//END S 

	//T
	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,100, 25,D3DXVECTOR3(700, GAME_HEIGHT*0.9f-100,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);

	id = om->GetNextID();
	
	objects->insert(std::make_pair(id, new TestBarrier(id,25, 75,D3DXVECTOR3(675, GAME_HEIGHT*0.9f-125,1),ObjectType::EnvironmentObject)));
	drawTree->AddToNode(om->GetObjectByID(id)->GetPosition().z, id);
	//END T

}

ObjectManager::ObjectManager()
{
	_currentMaxID=0;
}

ObjectManager::ObjectManager(Game* game)
{
	_currentMaxID=0;
	_game=game;

	unsigned int nextID = GetNextID();
	_player = new Player(nextID,D3DXVECTOR3(50,0,0));
	_objects.insert(std::make_pair(nextID,_player));
	_drawTree = new DepthTreeNode(_player->GetPosition().z, nextID);

	FakeFactory(&_objects,this, _drawTree);
}

ObjectManager::~ObjectManager()
{
	this->ShutDown();
	_game = NULL;
	_player = NULL;
}

bool ObjectManager::Initialize()
{
	for(unordered_map<unsigned int, GameObject*>::iterator itr = _objects.begin(); 
		itr!=_objects.end(); itr++)
	{
		if(!itr->second->Initialize(_game))
		{
			return false;
		}
	}
	return true;
}

void ObjectManager::Update(float elapsedTime)
{
	for(unordered_map<unsigned int, GameObject*>::iterator itr = _objects.begin();
		itr!=_objects.end(); itr++)
	{
		itr->second->Update(elapsedTime);
	}
	CollisionPair nextCol;

	//brute force collisions
	for(unordered_map<unsigned int, GameObject*>::iterator itr1 = _objects.begin();
		itr1!=_objects.end(); itr1++)
	{
		for(unordered_map<unsigned int, GameObject*>::iterator itr2 = _objects.begin();
			itr2!=_objects.end(); itr2++)
		{
			if(itr1->second->GetObjectType() != ObjectType::Background 
				&& itr2->second->GetObjectType()!=ObjectType::Background 
				&& itr1->second->GetID() != itr2->second->GetID())
			{
				if(!((itr1->second->GetObjectType() == ObjectType::EnvironmentObject || itr1->second->GetObjectType() == ObjectType::WallEnvironment || itr1->second->GetObjectType() == ObjectType::FloorEnvironment)
					&& (itr2->second->GetObjectType() == ObjectType::EnvironmentObject ||itr2->second->GetObjectType() == ObjectType::WallEnvironment || itr2->second->GetObjectType() == ObjectType::FloorEnvironment) ))
				{
					if(itr1->second->GetObjectType() != ObjectType::EnvironmentObject && itr2->second->GetObjectType()!=ObjectType::Background)
					{
						nextCol.IDA = itr1->second->GetID();
						nextCol.IDB = itr2->second->GetID();
						_collisionPairs.push(nextCol);
					}
				}
			}
		}
	}
	BruteForceCollision();
}

void ObjectManager::BruteForceCollision()
{
	CollisionPair next;
	GameObject *objA, *objB;
	D3DXVECTOR3 va,vb;
	while(!_collisionPairs.empty())
	{
		next = _collisionPairs.front();
		_collisionPairs.pop();
		objA = this->GetObjectByID(next.IDA);
		objB = this->GetObjectByID(next.IDB);
		
		while(objA->GetCollidable()->Intersects(objB->GetCollidable()))
		{
			va = objA->GetVelocity();
			vb = objB->GetVelocity();

			//invert
			va.x=va.x*-1.0f;
			va.y=va.y*-1.0f;
			vb.x=vb.x*-1.0f;
			vb.y=vb.y*-1.0f;

			D3DXVec3Normalize(&va,&va);
			D3DXVec3Normalize(&vb,&vb);
			
			objA->ProcessCollision(objB);
			objB->ProcessCollision(objA);
		}
	}
}

void ObjectManager::Draw()
{
	this->Draw(_drawTree);
}

void ObjectManager::Draw(DepthTreeNode * node)
{
	if(node->back!=NULL)
	{
		Draw(node->back);
	}

	Draw(node->objectIDs);

	if(node->front!=NULL)
	{
		Draw(node->front);
	}
}

void ObjectManager::Draw(vector<unsigned int> objects)
{
	for(unsigned int i = 0; i < objects.size(); i++)
	{
		this->GetObjectByID(objects[i])->Draw();
	}
}

void ObjectManager::ShutDown()
{
	for(unordered_map<unsigned int, GameObject*>::iterator itr = _objects.begin(); 
		itr!=_objects.end(); itr++)
	{
		if(itr->second!=NULL)
			itr->second->Shutdown();
	}
}

void ObjectManager::Reset()
{
	for(unordered_map<unsigned int, GameObject*>::iterator itr = _objects.begin(); 
		itr!=_objects.end();itr++)
	{
		itr->second->Reset();
	}
}

unsigned int ObjectManager::GetNextID()
{
	unsigned int id;
	if(!_unusedIDs.empty() && this->GetObjectByID(_unusedIDs.back())==NULL)
	{
		 id= _unusedIDs.back();	
		_unusedIDs.pop_back();
	}
	else
	{
		id = _currentMaxID;
		_currentMaxID++;
	}

	return id;
}

GameObject* ObjectManager::GetObjectByID(unsigned int ID)
{
	try
	{
		return _objects.at(ID);
	}
	catch(const std::out_of_range) //No object for given ID
	{
		return NULL;
	}
}
