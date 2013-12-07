#pragma once
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"

using namespace std;
//class ObjectManager;
class DepthTreeNode;

class Room
{
	public:
		Room();
		Room(vector<GameObject*>* objs);
		~Room();

		bool Initialize(ObjectManager* om);
		void Load(unordered_map<unsigned int,GameObject*>* objects, ObjectManager* om, DepthTreeNode* drawTree);
	protected:
	private:
		vector<GameObject*>* _objects;
		bool _isLoaded;
};

