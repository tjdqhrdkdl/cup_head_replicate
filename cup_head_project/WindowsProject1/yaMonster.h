#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Monster: public GameObject
	{
	public:
		float GetHp() { return mHp; }

		void SetHp(float hp) { mHp = hp; }

	protected:
		float mHp;
		bool onHit;
		float onHitChecker;
	};
}
