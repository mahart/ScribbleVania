#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Enemy.h"
#include "../Player/Player.h"
#include "../../DataStruct/Enums.h"

class FatFrogEnemy : public Enemy
{
	public:
		FatFrogEnemy();
		FatFrogEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p);
		~FatFrogEnemy();

		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		void AI();
	private:
		FatFrogState _state;
		Direction _dir;
		Player* _player;
		float _fallAccel;
		float _jumpTimer;
		float _jumpTime;
		void EnvironmentCollision(EnvironmentObject* obj);
		void DefaultCollision(GameObject* obj);
		void FloorCollision(EnvironmentObject* obj);
		void WallCollision(EnvironmentObject* obj);
		void PlayerCollision(Player* obj);
};

