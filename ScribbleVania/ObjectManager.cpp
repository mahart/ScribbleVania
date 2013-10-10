#include "ObjectManager.h"
#include "Player.h"

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
}

ObjectManager::~ObjectManager()
{
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
	//for now draw all objects "randomly" will enforce painters algorithm later;
	for(auto itr = _objects.begin(); itr!=_objects.end(); itr++)
	{
		itr->second->Draw();
	}
}

void ObjectManager::ShutDown()
{
	for(auto itr = _objects.begin(); itr!=_objects.end(); itr++)
	{
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