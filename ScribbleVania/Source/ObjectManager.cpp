#include "../Header/ObjectManager.h"
#include "../Header/GameObject/GameObject.h"
#include "../Header/GameObject/Player/Player.h"
#include "../Header/Room/Room.h"
#include "../Header/GameObject/Enemy.h"
#include "../Header/GameObject/GameObject.h"
#include "../Header/GameObject/Boss.h"

ObjectManager::ObjectManager()
{
	_currentMaxID=0;
}

ObjectManager::ObjectManager(Game* game)
{
	_currentMaxID=0;
	_game=game;

	unsigned int nextID = GetNextID();
	_player = new Player(nextID,D3DXVECTOR3(GAME_WIDTH/2,GAME_HEIGHT*0.2f,0),this);
	_objects.insert(std::make_pair(nextID,_player));
	_drawTree = new DepthTreeNode(_player->GetPosition().z, nextID);
	_factory = new ObjectFactory(this);
	this->room1 = _factory->MakeTestRoom1();
	this->room2 = _factory->MakeTestRoom2();
	this->room3 = _factory->MakeTestRoom3();
	MakeRooms();
	_treeLoaded=false;
	LoadRoom(Snail1);
	_snailDead = false;
	_frogDead = false;
}


void ObjectManager::MakeRooms()
{
	Snail1 =_factory->MakeS1();
	Snail2 = _factory->MakeS2();
	Snail3 = _factory->MakeS3();
	Snail4 = _factory->MakeS4();
	SnailB = _factory->MakeSB();
	Frog1 = _factory->MakeF1();
	Frog2 = _factory->MakeF2();
	Frog3 = _factory->MakeF3();
	FrogB = _factory->MakeFB();
	FinalRoom = _factory->MakeFinalRoom();
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
		if(!itr->second->Initialize(this))
		{
			return false;
		}
	}
	return true;
}

void ObjectManager::Update(float elapsedTime)
{
	if(elapsedTime > (1/30.0f))
		elapsedTime = (1/30.0f);
	if(_roomChanged)
	{
		_roomChanged=false;
		return;
	}
	for(unordered_map<unsigned int, GameObject*>::iterator itr = _objects.begin();
		itr!=_objects.end(); itr++)
	{
		if(!itr->second->IsDead())
			itr->second->Update(elapsedTime);
	}	

	//Remove objs
	unsigned int val;
	GameObject* obj;
	for(int i = _removeObjs.size()-1; i>=0; i--)
	{
		val = _removeObjs.front();
		_removeObjs.pop();
		obj = this->GetObjectByID(val);
		if(obj!=NULL)
		{
			_drawTree->Remove(obj->GetPosition().z, val);
			obj->Shutdown();
			_objects.erase(val);
		}
		SAFE_DELETE(obj);
	}

	//Add objs
	for(int i = _newObjs.size()-1; i >=0; i--)
	{
		obj = _newObjs.front();
		_newObjs.pop();
		_drawTree->AddToNode(obj->GetPosition().z, obj->GetID());
		_objects.insert(make_pair(obj->GetID(),obj));
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
			((Boss*)obj)->AI();
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
	GameObject *obj1, *obj2;
	D3DXVECTOR3 va,vb;

	//brute force collisions
	for(unordered_map<unsigned int, GameObject*>::iterator itr1 = _objects.begin();
		itr1!=_objects.end(); itr1++)
	{
		for(unordered_map<unsigned int, GameObject*>::iterator itr2 = _objects.begin();
			itr2!=_objects.end(); itr2++)
		{
			obj1 = itr1->second;
			obj2 = itr2->second;

			if(SkipPair(obj1,obj2))
				continue;

			nextCol.ID1 = obj1->GetID();
			nextCol.ID2 = obj2->GetID();
			_collisionPairs.push(nextCol);
		}
	}


	while(!_collisionPairs.empty())
	{
		next = _collisionPairs.front();
		_collisionPairs.pop();
		obj1 = this->GetObjectByID(next.ID1);
		obj2 = this->GetObjectByID(next.ID2);
		
		while(obj1->GetCollidable()->Intersects(obj2->GetCollidable()))
		{
			if(obj1->GetObjectType()==ObjectType::Projectile)
			{
				obj1->ProcessCollision(obj2);
				obj2->ProcessCollision(obj1);

				if(((Projectile*)obj1)->isDying())
					break;
			}
			else if(obj2->GetObjectType() == ObjectType::Projectile)
			{
				obj2->ProcessCollision(obj1);
				obj1->ProcessCollision(obj2);
				if(((Projectile*)obj2)->isDying())
					break;
			}
			else
			{
				obj1->ProcessCollision(obj2);
				obj2->ProcessCollision(obj1);
			}

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

bool ObjectManager::SkipPair(GameObject* obj1, GameObject* obj2)
{
	D3DXVECTOR3 va,vb;
	int id1,id2,owner1,owner2;
	ObjectType type1,type2;

	id1 = obj1->GetID();
	owner1 = obj1->GetOwnerID();
	type1 = obj1->GetObjectType();

	id2 = obj2->GetID();
	owner2 = obj2->GetOwnerID();
	type2 = obj2->GetObjectType();

	if(obj1->IsDead() || obj2->IsDead())
		return true;
	//Do not collide with the background, make sure environment objects are not colliding with eachother
	if(type1 == ObjectType::Background || 
		type2 == ObjectType::Background ||
		type1 == ObjectType::EnvironmentObject)
			return true;


	//Do not collide with something you own (projectiles), and do not collide with yourself
	if(id1 == owner2 || owner1 == id2 || id1 == id2 || owner1 == owner2)
		return true;

	//Skip projectile-projectile collisions
	if(type1 == ObjectType::Projectile && type2 == ObjecType::Projectile)
		return true;

	/*
	if(type1 == ObjectType::Enemy && ((Enemy*)obj1)->GetEnemyType() == EnemyType::FatFrog)
		return true;

	if(type2 == ObjectType::Enemy && ((Enemy*)obj2)->GetEnemyType() == EnemyType::FatFrog)
		return true;*/

	//Special enemy collision ignoring
	if((type1==ObjectType::Enemy || type1==ObjectType::Boss)&&(type2==ObjectType::Enemy || type2==ObjectType::Boss))
		return true;
	/*
	if(type1 == ObjectType::Enemy && type2 == ObjectType::Enemy)
	{
		EnemyType et1,et2;
		et1 = ((Enemy*)obj1)->GetEnemyType();
		et2 = ((Enemy*)obj2)->GetEnemyType();

		if((et1 == EnemyType::GraySnail || et1 == EnemyType::RedSnail) &&
			(et2 == EnemyType::GraySnail || et2 == EnemyType::RedSnail))
				return true;

		if((et1 == EnemyType::FatFrog || et1 == EnemyType::BombFrog) &&
			(et2 == EnemyType::FatFrog || et2 == EnemyType::BombFrog))
				return true;

	}
	else if(type1 == ObjectType::Enemy && type2 == ObjectType::Boss)
	{
		EnemyType et1;
		BossType bt2;
		et1 = ((Enemy*)obj1)->GetEnemyType();
		bt2 = ((Boss*)obj2)->GetBossType();

		if((et1 == EnemyType::GraySnail || et1 == EnemyType::RedSnail) && bt2 == BossType::Snail)
			return true;

		if((et1 == EnemyType::FatFrog||et1 == EnemyType::BombFrog)&&bt2==BossType::Frog)
			return true;
	}
	else if(type1==ObjectType::Boss && type2 == ObjectType::Enemy)
	{
		EnemyType et2;
		BossType bt1;

		et2 = ((Enemy*)obj2)->GetEnemyType();
		bt1 = ((Boss*)obj1)->GetBossType();

		if(bt1==BossType::Snail && (et2 == EnemyType::GraySnail || et2 == EnemyType::RedSnail))
			return true;

		if((et2 == EnemyType::FatFrog||et2 == EnemyType::BombFrog)&&bt1==BossType::Frog)
			return true;
	}*/

	return false;
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
	queue<unsigned int> deletedNums;
	for(unsigned int i = 0; i < objects.size(); i++)
	{
		if(this->GetObjectByID(objects[i])!=NULL)
			this->GetObjectByID(objects[i])->Draw();
		else
			deletedNums.push(i);
	}

	//clean up null ids
	vector<unsigned int>::iterator it = objects.begin();
	while(!deletedNums.empty())
	{
		objects.erase(it+deletedNums.front());
		deletedNums.pop();
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

	int newCount = _newObjs.size();
	GameObject* g;
	for(int i=0; i<newCount; i++)
	{
		g = _newObjs.front();
		_newObjs.pop();
		g->Shutdown();
		SAFE_DELETE(g);
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

void ObjectManager::AddObject(GameObject* obj)
{
	//_objects.insert(std::make_pair(obj->GetID(), obj));
	//_drawTree->AddToNode(obj->GetPosition().z,obj->GetID());
	obj->Initialize(this);
	_newObjs.push(obj);
}

void ObjectManager::RemoveObject(unsigned int id)
{
	_removeObjs.push(id);
}
