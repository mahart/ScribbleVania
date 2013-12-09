#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Projectile.h"

class ObjectManager;

class SnailBossProjectile : public Projectile
{
	public:
		SnailBossProjectile();
		SnailBossProjectile(unsigned int id, GameObject* owner);
		~SnailBossProjectile();
		void Update(float elapsedTime);
		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
		void ProcessCollision(GameObject* obj);
		unsigned int GetOwnerID();
	private:

};
