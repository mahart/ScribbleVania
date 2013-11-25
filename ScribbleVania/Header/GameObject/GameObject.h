#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Constants.h"
#include "../Game/Game.h"
#include "../DataStruct/Collidable.h"
#include <d3dx9math.h>
typedef enum class ObjectType
{
	Player = 0,
	Level=1,
	Background = 2,
	EnvironmentObject=3,
	Boss=4,
	Enemy=5,
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

		//Used to fix position after collision, if applicable
		virtual void ProcessCollision(GameObject* obj) {Update(1.0f);}

		//Startup and Shutdown
		virtual bool Initialize(Game* game) = 0;
		virtual bool Initialize(Game* game, D3DXVECTOR3 position)=0;
		virtual void Shutdown() = 0;

		virtual void Reset() =0;
		
		//Getters
		unsigned int GetID() {return _id;}
		virtual D3DXVECTOR3 GetPosition() {return _position;}
		virtual D3DXVECTOR3 GetVelocity() {return _velocity;}

		virtual D3DXVECTOR3 GetCenter()=0;

		virtual ObjectType GetObjectType() {return _type;}
		virtual Collidable* GetBounds() {return _bound;}

		virtual int GetWidth()=0;
		virtual int GetHeight()=0;

		virtual Collidable* GetCollidable(){return _bound;}
	protected:
		unsigned int _id;
		Game* _game;
		D3DXVECTOR3  _position;
		D3DXVECTOR3 _velocity;
		ObjectType _type;
		Collidable* _bound;
	private:

};