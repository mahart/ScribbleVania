#pragma once
#define WIN32_LEAN_AND_MEAN
#include "GameObject.h"
#include "../DataStruct/Enums.h"


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
		virtual void Update(float elapsedTime);
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
		virtual void AI()=0;
		EnemyType GetEnemyType(){return _enemyType;}
	protected:
		EnemyType _enemyType;
		Image objectImage;
		int _hitPoints;
		TextureManager objectTexture;
		D3DXVECTOR3 ExitObject(GameObject* obj);
	private:	
		
};

