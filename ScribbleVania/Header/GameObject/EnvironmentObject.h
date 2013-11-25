#pragma once
#define WIN32_LEAN_AND_MEAN

#include "GameObject.h"
#include "../Graphic/Image.h"
#include "../Graphic/TextureManager.h"

typedef enum class EnvSubType{
	Wall,
	Floor,
	Ceiling,
	Ledge,
	Door,
	Background,
	Other
} EnvSubType;

class EnvironmentObject : public  GameObject
{
	public:
		EnvironmentObject();
		EnvironmentObject(unsigned int ID);
		~EnvironmentObject();

		//Draw Will change when the graphics component is replaced
		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE);

		// Draw this image using the specified SpriteData.
		//   The current SpriteData.rect is used to select the texture.
		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter

		//Startup and Shutdown
		virtual void Shutdown();
		virtual bool Initialize(Game* game);
		virtual bool Initialize(Game* game, D3DXVECTOR3 position);

		virtual void Reset();
		virtual int GetWidth();
		virtual int GetHeight();
		virtual D3DXVECTOR3 GetCenter();
		//getter
		bool IsStatic() {return _static;}
		EnvSubType GetSubType(){return _subType;}
	protected:
		bool _static;
		EnvSubType _subType;
		Image objectImage;
		TextureManager objectTexture;
	private:
};
