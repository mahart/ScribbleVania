#pragma once
#define WIN32_LEAN_AND_MEAN
#include "GameObject.h"
#include "image.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "BoundingBox.h"

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
		Position GetCenter();
		//Startup and Shutdown
		bool Initialize(Game* game);
		void Shutdown();
		void Reset();
		int GetWidth();
		int GetHeight();
		void SetX(float x){_position.x = x;}
		void SetY(float y){_position.y = y;}
	protected:
		Image playerImage;
		TextureManager playerTexture;
	private:
};
