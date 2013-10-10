#pragma once
#define WIN32_LEAN_AND_MEAN

#include "Collidable.h"
#include "game.h"

class BoundingCircle;
class GameObject;

class BoundingBox : public Collidable
{
	public:
		BoundingBox(unsigned int ownerId, GameObject* ownerObject);
		~BoundingBox();

		virtual void Update(float elapsedTime);
		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);
		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		virtual bool Initialize(Game* game, int dimension1, int dimansion2);
		float Bottom();
		float Top();
		float Left();
		float Right();

		virtual void Reset();
		virtual void Shutdown();
		virtual bool Intersects(Collidable *c);
		virtual Position GetCenter();
	protected:
		int _width;
		int _height;
	private:
		bool IntersectB(BoundingBox *b);
		bool IntersectC(BoundingCircle *c);

		
};
