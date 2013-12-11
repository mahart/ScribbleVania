#pragma once
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <queue>
#include <unordered_map>
#include <queue>
#include "GameObject/EnvironmentObject.h"
#include "Game/Game.h"
#include "DataStruct/DepthTreeNode.h"
#include "Room/Room.h"
#include "GameObject/ObjectFactory.h"
#include "DataStruct/Enums.h"
class Player;
using namespace std;

struct CollisionPair
{
	unsigned int ID1;
	unsigned int ID2;
};

class GameObject;

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
		virtual Graphics* GetGraphics(){return _game->getGraphics();}
		virtual Input* GetInput(){return _game->getInput();}

		void AddObject(GameObject* obj);
		void MakeRooms();
		void RemoveObject(unsigned int _id);
		Room* room1;
		Room* room2;
		Room* room3;

		Room* Snail1;
		Room* Snail2;
		Room* Snail3;
		Room* Snail4;
		Room* SnailB;
		Room* Frog1;
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
		unordered_map<ProjectileType,Image> _projectiles;
		void BruteForceCollision();
	private:
		bool _roomChanged;
		bool _treeLoaded;
		ObjectFactory* _factory;
		queue<GameObject*> _newObjs;
		queue<unsigned int> _removeObjs;
		bool SkipPair(GameObject* obj1, GameObject* obj2);
};
