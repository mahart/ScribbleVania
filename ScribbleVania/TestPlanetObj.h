#ifndef _TEST_PLANET_OBJ_H
#define _TEST_PLANET_OBJ_H
#define WIN32_LEAN_AND_MEAN

#include "EnvironmentObject.h"

class TestPlanetObj : public EnvironmentObject
{
	public:
		TestPlanetObj();
		TestPlanetObj(unsigned int ID);
		~TestPlanetObj();

		bool Initialize(Game* game);
		void Update(float elapsedTime);
	protected:
	private:
};
#endif