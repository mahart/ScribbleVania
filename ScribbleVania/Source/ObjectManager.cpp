#include "../Header/ObjectManager.h"
#include "../Header/GameObject/Player/Player.h"
#include "../Header/Room/Room.h"
#include "../Header/GameObject/Enemy.h"


ObjectManager::ObjectManager()
{
	_currentMaxID=0;
}

ObjectManager::ObjectManager(Game* game)
{
	_currentMaxID=0;
	_game=game;

	unsigned int nextID = GetNextID();
	_player = new Player(nextID,D3DXVECTOR3(50,0,0),this);
	_objects.insert(std::make_pair(nextID,_player));
	_drawTree = new DepthTreeNode(_player->GetPosition().z, nextID);
	_factory = new ObjectFactory(this);

	this->room1 = _factory->MakeTestRoom1();
	this->room2 = _factory->MakeTestRoom2();
	this->room3 = _factory->MakeTestRoom3();

	_treeLoaded=false;
	LoadRoom(room2);
}

ObjectManager::~ObjectManager()
{
	this->ShutDown();
	_game = NULL;
	_player = NULL;
	_factory = NULL;
}

bool ObjectManager::LoadRoom(Room* room)
{
	if(_treeLoaded)
	{
		UnloadCurrentRoom();
	}

	room->Load(&this->_objects, this,this->_drawTree);
	
	_treeLoaded = true;
	_roomChanged=true;
	return false;
}

void ObjectManager::UnloadCurrentRoom()
{
	if(_drawTree==NULL)
	{
		return;
	}

	SAFE_DELETE(_drawTree);

	Player* p = (Player*)_objects.at(0);

	_objects.clear();
	_objects.insert(std::make_pair(0,p));
	_drawTree = new DepthTreeNode(p->GetPosition().z,p->GetID());
	
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
	if(_roomChanged)
	{
		_roomChanged=false;
		return;
	}
	for(unordered_map<unsigned int, GameObject*>::iterator itr = _objects.begin();
		itr!=_objects.end(); itr++)
	{
		itr->second->Update(elapsedTime);
	}	
}

void ObjectManager::AI()
{
	GameObject* obj;
	for(unordered_map<unsigned int, GameObject*>::iterator itr = _objects.begin();
		itr!=_objects.end(); itr++)
	{
		obj = itr->second;
		if(obj->GetObjectType()==ObjectType::Enemy)
		{
			((Enemy*)obj)->AI();
		}
		else if(obj->GetObjectType()==ObjectType::Boss)
		{
			//update boss
		}
	}	
}

void ObjectManager::Collision()
{
	BruteForceCollision();
}

void ObjectManager::BruteForceCollision()
{
	CollisionPair nextCol;
	CollisionPair next;
	GameObject *objA, *objB;
	D3DXVECTOR3 va,vb;

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
				if(!(itr1->second->GetObjectType() == ObjectType::EnvironmentObject 
					&& itr2->second->GetObjectType() == ObjectType::EnvironmentObject))
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

			if(_roomChanged)
			{
				while(!_collisionPairs.empty())
				{
					_collisionPairs.pop();
				}
				Initialize();
				return;
			}
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
	SAFE_DELETE(_factory);
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
