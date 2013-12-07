#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../EnvironmentObject.h"

class TestPlanetObj : public EnvironmentObject
{
	public:
		TestPlanetObj();
		TestPlanetObj(unsigned int ID);
		~TestPlanetObj();

		bool Initialize(ObjectManager* om);
		bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
		void Update(float elapsedTime);
		void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);
	protected:
	private:
};