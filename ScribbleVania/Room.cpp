#include "Room.h"

Room::Room() : GameObject()
{

}

Room::Room(unsigned int ID) : GameObject(ID)
{
}

Room::~Room()
{
}

void Room::Update(float elapsedTime)
{
	for each (EnvironmentObject* var in envList)
	{
		var->Update(elapsedTime);
	}

	background->Update(elapsedTime);
}

void Room::Draw( COLOR_ARGB color )
{
	for each (EnvironmentObject* var in envList)
	{
		var->Draw(color);
	}

	background->Draw(color);
}

void Room :: Draw(SpriteData sd, COLOR_ARGB color )
{
	for each (EnvironmentObject* var in envList)
	{
		var->Draw(sd, color);
	}

	background->Draw(sd, color);
}

