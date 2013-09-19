#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
#include "image.h"
#include "TextureManager.h"
#define WIN32_LEAN_AND_MEAN

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

		//Startup and Shutdown
		bool Initialize(Game* game);
		void Shutdown();
		void Reset();
	protected:
		Image playerImage;
		TextureManager playerTexture;
	private:
};

#endif