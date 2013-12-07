#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Enemy.h"
#include "../Player/Player.h"
#include "../../DataStruct/Enums.h"


class RedSnailEnemy : public Enemy
{
	public:
		RedSnailEnemy();
		RedSnailEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p);

		~RedSnailEnemy();

		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		void AI();

	private:
		void EnvironmentCollision(EnvironmentObject* obj);
		void DefaultCollision(GameObject* obj);
		void FloorCollision(EnvironmentObject* obj);
		void WallCollision(EnvironmentObject* obj);
		void PlayerCollision(Player* obj, D3DXVECTOR3 direction);
		float _fallAccel;
		float _accel;
		RedSnailState _state;
		Direction _dir;
		Player* _player;
};
