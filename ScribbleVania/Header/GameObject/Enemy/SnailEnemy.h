#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Enemy.h"
typedef enum class SlugState
{
	Patrol,
	Attack,
	Dead
} SlugState;



class SnailEnemy : public Enemy
{
	public:
		SnailEnemy();
		SnailEnemy(unsigned int ID, D3DXVECTOR3 position);

		~SnailEnemy();

		bool Initialize(Game* game);
		bool Initialize(Game* game, D3DXVECTOR3 position);
		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		void AI();
		void DefaultCollision(GameObject* obj);
	private:
		float _fallAccel;
		float _accel;
};
