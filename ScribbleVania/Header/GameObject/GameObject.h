#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../Constants.h"
#include "../Game/Game.h"
#include "../DataStruct/Collidable.h"
#include <d3dx9math.h>
#include <vector>
#include "../DataStruct/Enums.h"

class ObjectManager;
class GameObject
{
	public:
		GameObject(){}
		GameObject(unsigned int id){_id=id;_visible=true;}
		virtual ~GameObject(){}
		
		//Draw Will change when the graphics component is replaced
		virtual void Draw(COLOR_ARGB color = graphicsNS::WHITE) = 0;

		// Draw this image using the specified SpriteData.
		virtual void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE) = 0; // draw with SpriteData using color as filter
		
		virtual void Update(float elapsedTime) = 0;

		//Used to fix position after collision, if applicable
		virtual void ProcessCollision(GameObject* obj) {Update(0.0f);}

		//Startup and Shutdown
		virtual bool Initialize(ObjectManager* om) = 0;
		virtual bool Initialize(ObjectManager* om, D3DXVECTOR3 position)=0;
		virtual void Shutdown() = 0;

		virtual void Reset() = 0;
		
		virtual bool IsVisible(){return _visible;}

		//Getters
		unsigned int GetID() {return _id;}
		virtual D3DXVECTOR3 GetPosition() {return _position;}
		virtual D3DXVECTOR3 GetVelocity() {return _velocity;}

		virtual D3DXVECTOR3 GetCenter()=0;

		virtual D3DXVECTOR3 GetDirection(){return D3DXVECTOR3(0,0,0);}

		virtual ObjectType GetObjectType() {return _type;}
		virtual Collidable* GetBounds() {return _bound;}

		//Returns the ID of the object that owns this object, most objects will own themselves.
		virtual unsigned int GetOwnerID(){return _id;}
		
		//Adds the given id to the objects owned by this object
		virtual void AddToOwned(unsigned int id){_ownedIDs.push_back(id);}

		//Removes the given id from the objects owned by this object
		virtual void RemoveFromOwned(unsigned int id)
		{
			std::vector<unsigned int>::iterator it =_ownedIDs.begin();
			for(;it!=_ownedIDs.end();it++)
				if(*it=id)
					break;
			_ownedIDs.erase(it);
		}

		//Removes all objects owned by this object
		virtual void RemoveAllOwned(){while(!_ownedIDs.empty()) _ownedIDs.erase(_ownedIDs.begin());}

		//Get the width of the GameObject
		virtual int GetWidth()=0;
		virtual int GetHeight()=0;
		virtual float GetScale()=0;
		virtual Collidable* GetCollidable(){return _bound;}
	protected:
		unsigned int _id;
		bool _visible;
		D3DXVECTOR3  _position;
		D3DXVECTOR3 _startPosition;
		D3DXVECTOR3 _velocity;
		ObjectType _type;
		Collidable* _bound;
		ObjectManager* _om;
		std::vector<unsigned int> _ownedIDs;
	private:	
};