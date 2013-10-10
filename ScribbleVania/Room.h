#pragma once
#define WIN32_LEAN_AND_MEAN

#include "GameObject.h"
#include <vector>
#include "EnvironmentObject.h"
using namespace std;

class Room : public GameObject
{
	public:
		Room();
		Room(unsigned int ID);
		virtual ~Room();

		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE);

		// Draw this image using the specified SpriteData.
		//   The current SpriteData.rect is used to select the texture.
		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE); // draw with SpriteData using color as filter
		
		virtual void Update(float elapsedTime);

		//Startup and Shutdown
		virtual bool Initialize(Game* game) = 0;
		virtual void Shutdown() = 0;

		virtual void Reset() =0;
	protected:
		vector<EnvironmentObject *> envList;
		EnvironmentObject * background;
	private:
};