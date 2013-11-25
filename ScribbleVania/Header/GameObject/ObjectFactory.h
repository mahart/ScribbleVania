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

	Room* MakeTestRoom1();
	Room* MakeTestRoom2();
	Room* MakeTestRoom3();
private:
	ObjectManager* _om;
};

