#pragma once
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "game.h"
#include "Collidable.h"
#include "GameStructs.h"
typedef enum class ObjectType
{
	Player = 0,
	Level=1,
	Background = 2,
	EnvironmentObject=3,
	Boss=4,
	Enemy =5,
	Other
} ObjecType;


//virtual class, used as an interface
class GameObject
{
	public:
		GameObject(){}
		GameObject(unsigned int id){_id=id;}
		virtual ~GameObject(){}
		
		//Draw Will change when the graphics component is replaced
		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE) = 0;

		// Draw this image using the specified SpriteData.
		//   The current SpriteData.rect is used to select the texture.
		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE) = 0; // draw with SpriteData using color as filter
		
		virtual void Update(float elapsedTime) = 0;

		//Startup and Shutdown
		virtual bool Initialize(Game* game) = 0;
		virtual void Shutdown() = 0;

		virtual void Reset() =0;
		
		//Getters
		unsigned int ID() {return _id;}
		virtual float getX() {return _position.x;}
		virtual float getY() {return _position.y;}
		virtual Position GetCenter()=0;
		virtual float getDepth() {return _position.depth;}
		virtual ObjectType getObjectType() {return _type;}
		virtual Collidable* getBounds() {return _bound;}
		virtual int GetWidth()=0;
		virtual int GetHeight()=0;
		virtual Collidable* GetCollidable(){return _bound;}
	protected:
		unsigned int _id;
		Game* _game;
		Position _position;
		ObjectType _type;
		Collidable* _bound;
	private:

};