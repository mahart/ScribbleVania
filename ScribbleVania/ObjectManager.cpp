#include "ObjectManager.h"
#include "Player.h"
#include "TestPlanetObj.h"
#include "TestBackground.h"

static void FakeFactory(unordered_map<unsigned int,GameObject*>* objects, ObjectManager* om, DepthTreeNode* drawTree)
{
	unsigned int id = om->GetNextID();
	objects->insert(std::make_pair(id,new TestPlanetObj(id)));
	if(drawTree == NULL)
	{
		drawTree = new DepthTreeNode(om->GetObjectByID(id)->getDepth(),id);
	}
	else
	{
		drawTree->AddToNode(om->GetObjectByID(id)->getDepth(), id);
	}

	id = om->GetNextID();
	objects->insert(std::make_pair(id, new TestBackGround(id)));
	drawTree->AddToNode(om->GetObjectByID(id)->getDepth(), id);

}

ObjectManager::ObjectManager()
{
	_currentMaxID=0;
}

ObjectManager::ObjectManager(Game* game)
{
	_game=game;
	unsigned int nextID = GetNextID();
	_player = new Player(nextID);
	_objects.insert(std::make_pair(nextID,_player));
	_drawTree = new DepthTreeNode(_player->getDepth(), nextID);
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
	for(auto itr = _objects.begin(); itr!=_objects.end(); itr++)
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
	for(auto itr = _objects.begin(); itr!=_objects.end(); itr++)
	{
		itr->second->Update(elapsedTime);
	}
}

void ObjectManager::Draw()
{
	this->Draw(_drawTree);
	/*//for now draw all objects "randomly" will enforce painters algorithm later;
	for(auto itr = _objects.begin(); itr!=_objects.end(); itr++)
	{
		itr->second->Draw();
	}*/
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
	for(auto itr = _objects.begin(); itr!=_objects.end(); itr++)
	{
		if(itr->second!=NULL)
			itr->second->Shutdown();
	}
}

void ObjectManager::Reset()
{
	for(auto itr = _objects.begin(); itr!=_objects.end();itr++)
	{
		itr->second->Reset();
	}
}

unsigned int ObjectManager::GetNextID()
{
	unsigned int id;
	if(_unusedIDs.size()>0)
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
	return _objects.at(ID);
}
