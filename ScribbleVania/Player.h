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
	jumping
} PlayerState;

class Player : public  GameObject
{
	public:
		Player();
		Player(unsigned int id);
		virtual ~Player();

		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		// Draw this image using the specified SpriteData.
		//   The current SpriteData.rect is used to select the texture.
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter
		
		void Update(float elapsedTime);
		void Update(float elapsedTime, D3DXVECTOR3 invVelocity);
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
		PlayerState _state;
		float _fallAccel;
};
