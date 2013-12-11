#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Enemy.h"
#include "../Player/Player.h"
#include "../../DataStruct/Enums.h"


class BombFrogEnemy : public Enemy
{
	public:
		BombFrogEnemy();
		BombFrogEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p);
		BombFrogEnemy(unsigned int ID, D3DXVECTOR3 position, Player* p, unsigned int owner);
		~BombFrogEnemy();

		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter
		void AI();
		unsigned int GetOwnerID(){return _ownerID;}
		bool IsDead(){return _state==FatFrogState::Dead;}
	private:
		unsigned int _ownerID;
		FatFrogState _state;
		Direction _dir;
		Player* _player;
		float _fallAccel;
		float _jumpTimer;
		float _jumpTime;
		int _jumpCount;
		int _maxJumps;
		void Jump();

		void EnvironmentCollision(EnvironmentObject* obj);
		void DefaultCollision(GameObject* obj);
		void FloorCollision(EnvironmentObject* obj);
		void WallCollision(EnvironmentObject* obj);
		void PlayerCollision(Player* obj);
};

