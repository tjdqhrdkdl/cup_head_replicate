#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Collider;
	class Animator;
	class Monster: public GameObject
	{
	public:
		Monster();
		~Monster();

		float GetHp() { return mHp; }

		void SetHp(float hp) { mHp = hp; }
		bool GetOnHit() { return onHit; }
		float GetOnHitChecker() { return onHitChecker; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void OnHitCheck();
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
	protected:
		Animator* mAnimator;
		float mHp;
		bool onHit;
		float onHitChecker;
		bool mDead;
	};
}
