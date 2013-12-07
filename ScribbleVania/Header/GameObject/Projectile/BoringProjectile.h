#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Projectile.h"

class ObjectManager;

class BoringProjectile : public Projectile
{
	public:
		BoringProjectile();
		BoringProjectile(unsigned int id, GameObject* owner);
		~BoringProjectile();

		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
		void ProcessCollision(GameObject* obj);
		unsigned int GetOwnerID();
	protected:
	private:
};

