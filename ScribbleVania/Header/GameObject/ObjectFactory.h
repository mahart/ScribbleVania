#pragma once
#define WIN32_LEAN_AND_MEAN
class ObjectManager;
class Room;
class ObjectFactory
{
public:
	ObjectFactory();
	ObjectFactory(ObjectManager* om);
	~ObjectFactory();

	Room* MakeS1();
	Room* MakeS2();
	Room* MakeS3();
	Room* MakeS4();
	Room* MakeSB();

	Room* MakeF1();
	Room* MakeF2();
	Room* MakeF3();
	Room* MakeFB();

	Room* MakeFinalRoom();

	Room* MakeTestRoom1();
	Room* MakeTestRoom2();
	Room* MakeTestRoom3();

	
private:
	ObjectManager* _om;
};

