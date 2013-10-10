#pragma once
#define WIN32_LEAN_AND_MEAN
#include "graphics.h"
#include "GameStructs.h"
#include "image.h"
#include "TextureManager.h"
#include "game.h"
class GameObject;

enum CollidableType
{
	Box,
	Circle,
	Other,
};

class Collidable
{
public:
	Collidable(){/*Do nothing*/}
	virtual ~Collidable(){/*do nothing*/}

	virtual void Update(float elapsedTime)=0;
	virtual bool Initialize(Game* game, int dimension1, int dimansion2)=0;

	//Debug Function
	virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE)=0;
	virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE)=0;
	virtual void Reset()=0;
	virtual void Shutdown()=0;
	virtual bool Intersects(Collidable *c)=0;
	CollidableType Type(){return _type;}
	virtual Position GetCenter()=0;
protected:
	GameObject* _owner;
	CollidableType _type;
	//Debug objects
	Image _image;
	TextureManager _texture;
private:
};

