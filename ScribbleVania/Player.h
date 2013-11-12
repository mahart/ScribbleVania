#pragma once
#define WIN32_LEAN_AND_MEAN
#include "GameObject.h"
#include "image.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "BoundingBox.h"
typedef enum class PlayerState
{
	walking,
	sliding,
	jumping
} PlayerState;

class Player : public  GameObject
{
	public:
		Player();
		Player(unsigned int id);
		Player(unsigned int id, D3DXVECTOR3 position);
		virtual ~Player();

		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		// Draw this image using the specified SpriteData.
		//   The current SpriteData.rect is used to select the texture.
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter
		
		void Update(float elapsedTime);
		void ProcessCollision(GameObject* obj);
		D3DXVECTOR3 GetCenter();
		//Startup and Shutdown
		bool Initialize(Game* game);
		bool Initialize(Game* game, D3DXVECTOR3 position);

		void Shutdown();
		void Reset();
		int GetWidth();
		int GetHeight();
	protected:
		float _accel;
		Image playerImage;
		TextureManager playerTexture;
	private:
		int _jumpCount;
		int _jumpMax;
		PlayerState _state;
		float _fallAccel;
		bool _onGround;
		bool _onLeft;
		void WallCollision(EnvironmentObject* obj);
		void FloorCollision(EnvironmentObject* obj);
		void DefaultCollision(GameObject* obj); 
		void UpdateJumping(float elapsedTime,Input* input);
		void UpdateWalking(float elapsedTime,Input* input);
		void UpdateSliding(float elapsedTime,Input* input);
};
