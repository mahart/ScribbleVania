#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../EnvironmentObject.h"
#include "../../Room/Room.h"

class Door : public EnvironmentObject
{
public:
	Door();
	Door(unsigned int ID, int height, int width, D3DXVECTOR3 position, D3DXVECTOR3 exit, Room** room);
	~Door();
	
	bool Initialize(ObjectManager* om);
	bool Initialize(ObjectManager* om, D3DXVECTOR3 position);
	void Update(float elapsedTime);
	void Draw(COLOR_ARGB color = graphicsNS::WHITE);
	void Draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);
	Room* GetRoom();
	void ProcessCollision(GameObject* obj);
	D3DXVECTOR3 GetExit();
	bool SwitchOpenClose();
	bool IsOpen(){return _open;}
protected:
private:
	Room** _room;
	bool _open;
	D3DXVECTOR3 _exit;
	unsigned int _width;
	unsigned int _height;
};

