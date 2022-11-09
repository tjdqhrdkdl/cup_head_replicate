#pragma once
#include "yaGameObject.h"
namespace ya {
	class Meteor:public GameObject
	{
	public:
		Meteor();
		~Meteor() = default;
		void Render(HDC hdc);
		void Tick();
		

	private:
		float mSpeed;
		HPEN mPen;
		HBRUSH mBrush;
	};
}
