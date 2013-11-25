#pragma once
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <unordered_map>
#include <queue>
#include "GameObject/GameObject.h"
#include "GameObject/EnvironmentObject.h"
#include "Game/Game.h"
#include "DataStruct/DepthTreeNode.h"
#include "Room/Room.h"
#include "GameObject\ObjectFactory.h"

class Player;
using namespace std;

struct CollisionPair
{
	unsigned int IDA;
	unsigned int IDB;
};

class ObjectManager
{
	public:
		ObjectManager();
		ObjectManager(Game* game);
		~ObjectManager();
		
		bool Initialize();
		void Update(float elapsedTime);
		void AI();
		void Collision();

		void Draw();
		void ShutDown();
		void Reset();
		unsigned int GetNextID();
		GameObject* GetObjectByID(unsigned int ID);
		//loadlevel
		//switchlevelv
		bool LoadRoom(Room* room);
		void UnloadCurrentRoom();

		Room* room1;
		Room* room2;
		Room* room3;
	protected:
		//loadroom
		//switchroom
		Game* _game;
		DepthTreeNode* _drawTree; 
		unsigned int _currentMaxID;
		vector<unsigned int> _unusedIDs;
		unordered_map<unsigned int,GameObject*> _objects;
		Player* _player;
		vector<EnvironmentObject*> _environment;
		void Draw(DepthTreeNode*node);
		void Draw(vector<unsigned int> objects);
		queue<CollisionPair> _collisionPairs;
		
		void BruteForceCollision();
	private:
		bool _roomChanged;
		bool _treeLoaded;
		ObjectFactory* _factory;
};
