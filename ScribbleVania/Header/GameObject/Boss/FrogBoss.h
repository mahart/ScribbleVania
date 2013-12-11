#pragma once
#define WIN32_LEAN_AND_MEAN
#include "../Boss.h"
#include "../Player/Player.h"

class FrogBoss : public Boss
{
	public:
		FrogBoss();
		FrogBoss(unsigned int ID, Player* p,D3DXVECTOR3 position);
		~FrogBoss();

		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);

		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);

		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		void AI();
		bool IsDead(){return _state == FrogBossState::Dead;}
	private:
		Player* _player;
		Direction _dir;
		float _fallAccel;
		FrogBossState _state;
		bool _wasHit;
		bool _switchToGlide;

		float _glideShotTimer;
		float _glideShotTime;

		int _hitCount;
		int _hitThreshold;

		int _jumpCount;
		int _maxJumpCount;
		void Jump();
		void UpdateFall(float elapsedTime);
		void UpdateJump(float elapsedTime);
		void UpdateGlide(float elapsedTime);
		void UpdatePatrol(float elapsedTime);

		void EnvironmentCollision(EnvironmentObject* obj);
		void FloorCollision(EnvironmentObject* obj);
		void WallCollision(EnvironmentObject* obj);
		void PlayerCollision(Player* obj);
		void ProjectileCollision(Projectile* obj);
		void DefaultCollision(GameObject* obj);
};

