#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Monster: public GameObject
	{
	public:
		float GetHp() { return mHp; }

		void SetHp(float hp) { mHp = hp; }
		bool GetOnHit() { return onHit; }
		float GetOnHitChecker() { return onHitChecker; }

	protected:
		float mHp;
		bool onHit;
		float onHitChecker;
	};
}
