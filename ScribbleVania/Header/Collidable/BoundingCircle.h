#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../DataStruct/Collidable.h"
class BoundingBox;

class BoundingCircle : public Collidable
{
	public:
		BoundingCircle(unsigned int ownerId, GameObject* ownerObject);
		~BoundingCircle();

		virtual void Update(float elapsedTime);
		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);
		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE);
		virtual bool Initialize(Game* game, int radius, int UNUSED);
		float Radius();

		virtual void Reset();
		virtual void Shutdown();
		virtual bool Intersects(Collidable *c);
		virtual D3DXVECTOR3 GetCenter();
		virtual D3DXVECTOR3 GetNearestPoint(D3DXVECTOR3 center);
	protected:
		int _radius;
	private:
		bool IntersectC(BoundingCircle *c);
		bool IntersectB(BoundingBox *b);
};
