#include "../../Header/Room/Room.h"
#include "../../Header/ObjectManager.h"
//#include "../../Header/DataStruct/DepthTreeNode.h"

Room::Room()
{
	_isLoaded=false;
}

Room::Room(vector<GameObject*>* objs)
{
	_isLoaded=false;
	_objects = objs;
}

Room::~Room()
{
	for(int i = _objects->size()-1; i>=0; i--)
	{
		SAFE_DELETE(_objects->at(i));
	}

	SAFE_DELETE(_objects);
}

void Room::Load(unordered_map<unsigned int,GameObject*>* objects, ObjectManager* om, DepthTreeNode* drawTree)
{
	for(unsigned int i = 0; i <_objects->size(); i++)
	{
		objects->insert(std::make_pair(_objects->at(i)->GetID(),_objects->at(i)));
		drawTree->AddToNode(_objects->at(i)->GetPosition().z,_objects->at(i)->GetID());
	}
}

bool Room::Initialize(Game *game)
{
	bool result = true;
	for(unsigned int i =0; i<_objects->size(); i++)
	{
		result = result && _objects->at(i)->Initialize(game);
	}
	_isLoaded=false;
	return result;
}