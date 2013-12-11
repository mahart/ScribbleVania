#pragma once
#define WIN32_LEAN_AND_MEAN
#include "../Boss.h"
#include "../Player/Player.h"
class SnailBoss : public Boss
{
	public:
		SnailBoss();
		SnailBoss(unsigned int ID, Player* p);
		~SnailBoss();

		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);

		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);

		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		D3DXVECTOR3 GetDirection();
		void AI();
		bool IsDead(){return _state == SnailBossState::Dead;}
	protected:
	private:
		int _hitPoints;
		int _hitThreshold;
		int _hitCount;
		int _bounceCount;
		float _bounceTimer;
		float _startBounceTime;
		float _attackTimer;
		float _bounceCountStop;
		Player* _player;
		SnailBossState _state;
		float _fallAccel;
		float _accel;
		Direction _dir;
		void UpdateFalling(float elapsedTime);
		void UpdateBouncing(float elapsedTime);
		void UpdateAttacking(float elapsedTime);

		void EnvironmentCollision(EnvironmentObject* obj);
		void FloorCollision(EnvironmentObject* obj);
		void WallCollision(EnvironmentObject* obj);

		void SwitchBouncing();
		void SwitchStanding();
};
