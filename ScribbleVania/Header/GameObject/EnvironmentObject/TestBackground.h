#pragma once
#define WIN32_LEAN_AND_MEAN

#include "../EnvironmentObject.h"

class TestBackGround : public EnvironmentObject
{
	public:
		TestBackGround();
		TestBackGround(unsigned int ID);
		~TestBackGround();

		bool Initialize(Game* game);
		bool Initialize(Game* game, D3DXVECTOR3 position);
		void Update(float elapsedTime);
	protected:
	private:
};
