#ifndef _BACKGROUND_H
#define _BACKGROUND_H
#define WIN32_LEAN_AND_MEAN

#include "EnvironmentObject.h"

class TestBackGround : public EnvironmentObject
{
	public:
		TestBackGround();
		TestBackGround(unsigned int ID);
		~TestBackGround();

		bool Initialize(Game* game);
		void Update(float elapsedTime);
	protected:
	private:
};
#endif