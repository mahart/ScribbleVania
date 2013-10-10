#pragma once
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <unordered_map>
#include "GameObject.h"
#include "EnvironmentObject.h"
#include "game.h"

class Player;
using namespace std;

class ObjectManager
{
	public:
		ObjectManager();
		ObjectManager(Game* game);
		~ObjectManager();

		bool Initialize();
		void Update(float elapsedTime);
		void Draw();
		void ShutDown();
		void Reset();

		//loadlevel
		//switchlevel
		
	protected:
		//loadroom
		//switchroom
		Game* _game;
		unsigned int _currentMaxID;
		vector<unsigned int> _unusedIDs;
		unordered_map<unsigned int,GameObject*> _objects;
		Player* _player;
		vector<EnvironmentObject*> _environment;
		unsigned int GetNextID();
	private:
		
};
