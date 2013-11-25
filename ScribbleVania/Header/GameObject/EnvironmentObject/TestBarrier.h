#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../EnvironmentObject.h"

class TestBarrier : public EnvironmentObject
{
	public:
		TestBarrier();
		TestBarrier(unsigned int ID, unsigned int height, unsigned int width,D3DXVECTOR3 position, EnvSubType type);
		~TestBarrier();

		bool Initialize(Game* game);
		bool Initialize(Game* game, D3DXVECTOR3 position);
		void Update(float elapsedTime);
		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);
	protected:
	private:
		unsigned int _width;
		unsigned int _height;
};