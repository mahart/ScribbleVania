#pragma once
#define WIN32_LEAN_AND_MEAN
#include "../GameObject.h"
#include "../../Graphic/Image.h"
#include "../../Graphic/TextureManager.h"
#include "../../ObjectManager.h"
#include "../../Collidable/BoundingBox.h"
#include "../EnvironmentObject/Door.h"
#include "../../Room/Room.h"
#include "../../DataStruct/Enums.h"
#include "../Projectile/BoringProjectile.h"

class Player : public  GameObject
{
	public:
		Player();
		Player(unsigned int id);
		Player(unsigned int id, D3DXVECTOR3 position, ObjectManager* om);
		virtual ~Player();

		void Damage(float dmg){};
		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		// Draw this image using the specified SpriteData.
		//   The current SpriteData.rect is used to select the texture.
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter
		
		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		D3DXVECTOR3 GetCenter();
		//Startup and Shutdown
		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 distance);

		D3DXVECTOR3 GetDirection();
		void DBounce(D3DXVECTOR3 direction);
		void VBounce(D3DXVECTOR3 direction);

		void Shutdown();
		void Reset();
		int GetWidth();
		int GetHeight();
		float GetScale();
	protected:
		float _accel;
		Image playerImage;
		TextureManager playerTexture;
	private:
		int _jumpCount;
		int _jumpMax;
		float _shotTimer;
		GameObject* _touchedObj;
		bool _climbing;
		PlayerState _state;
		float _fallAccel;
		bool _onLeft;
		ObjectManager* _om;
		BoringProjectile p;

		D3DXVECTOR3 ExitObject(GameObject* obj);

		void EnvironmentCollision(EnvironmentObject* obj, D3DXVECTOR3 direction);
			void WallCollision(EnvironmentObject* obj,D3DXVECTOR3 direction);
			void FloorCollision(EnvironmentObject* obj);
			void LedgeCollision(EnvironmentObject* obj,D3DXVECTOR3 direction);
			void DoorCollision(Door* door);
		void DefaultCollision(GameObject* obj);

		void UpdateHanging(float elapsedTime, Input* input);
		void UpdateJumping(float elapsedTime,Input* input);
		void UpdateWalking(float elapsedTime,Input* input);
		void UpdateSliding(float elapsedTime,Input* input);

};
