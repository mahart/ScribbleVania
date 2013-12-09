#pragma once
#define WIN32_LEAN_AND_MEAN
#include "GameObject.h"
#include "../DataStruct/Enums.h"

class Projectile : public GameObject
{
	public:
		Projectile();
		Projectile(unsigned int id);
		~Projectile();

		void Update(float elapsedTime);

		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE);

		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter

		//Startup and Shutdown
		virtual bool Initialize(ObjectManager* om);
		virtual bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
		virtual void Shutdown();

		virtual void Reset();
		
		//Getters
		virtual D3DXVECTOR3 GetCenter();
		virtual int GetWidth();
		virtual int GetHeight();
		virtual float GetScale();
		void ProcessCollision(GameObject* obj);
		virtual void AI(){/*Do Nothing. Exists for if I make "smart" projectiles*/};
		ProjectileType GetProjectileType(){return _projectileType;}	
		bool isDying(){return _dying;}
	protected:
		GameObject* _owner;
		bool _dying;
		ProjectileType _projectileType;
		Image _projectileImage;
		TextureManager _projectileTexture;
		float _baseSpeed;
	private:

};
