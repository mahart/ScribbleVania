#pragma once
#define WIN32_LEAN_AND_MEAN
#include <d3dx9math.h>
#include "../Graphic/Graphics.h"
#include "../Graphic/Image.h"
#include "../Graphic/TextureManager.h"
#include "../Game/Game.h"
#include "../Constants.h"
#include "Enums.h"
class GameObject;

class ObjectManager;
class Collidable
{
public:
	Collidable(){/*Do nothing*/}
	virtual ~Collidable(){/*do nothing*/}

	//Update the collidable position (and image if debugging)
	virtual void Update(float elapsedTime)=0;

	//Initialize the collidable, dimension1 and dimension2 = height and width for squares, dimension1 =radius and dimension2 = unused for circles.
	virtual bool Initialize(ObjectManager* om, int dimension1, int dimansion2)=0;
	
	//Debug Function
	virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE)=0;
	virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE)=0;

	virtual void Reset()=0;
	virtual void Shutdown()=0;

	//Check if this collidable intersects c
	virtual bool Intersects(Collidable *c)=0;

	//gets the type fo the collidable (square, circle, other)
	CollidableType Type(){return _type;}

	//Gets the center of the collidable
	virtual D3DXVECTOR3 GetCenter()=0;

	//Gets this collidables nearest point to the given center, used for exiting objects
	virtual D3DXVECTOR3 GetNearestPoint(D3DXVECTOR3 center)=0;
protected:
	GameObject* _owner;
	CollidableType _type;
	ObjectManager* _om;
	//Debug object
	Image _image;
	//Debug object
	TextureManager _texture;

private:
};

