#pragma once
#define WIN32_LEAN_AND_MEAN
#include "GameObject.h"

typedef enum class EnemyType
{
	SnailEnemy,
	Other
} EnemyType;

class Enemy : public GameObject
{
	public:
		Enemy();
		Enemy(unsigned int ID);
		~Enemy();
	
		//Draw Will change when the graphics component is replaced
		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE);

		// Draw this image using the specified SpriteData.
		//   The current SpriteData.rect is used to select the texture.
		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter

		//Used to fix position after collision, if applicable
		virtual void ProcessCollision(GameObject* obj)=0;

		//Startup and Shutdown
		virtual bool Initialize(Game* game);
		virtual bool Initialize(Game* game, D3DXVECTOR3 position);
		virtual void Shutdown();

		virtual void Reset();
		
		//Getters
		virtual D3DXVECTOR3 GetCenter();
		virtual int GetWidth();
		virtual int GetHeight();
		virtual void AI()=0;
		EnemyType GetEnemyType(){return _enemyType;}
	protected:
		EnemyType _enemyType;
		Image objectImage;
		TextureManager objectTexture;
	private:	
};

