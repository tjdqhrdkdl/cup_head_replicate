#pragma once
#include "yaGameObject.h"

namespace ya 
{
	class Animator;
	class BeppiPh2Body: public GameObject
	{
	public:
		BeppiPh2Body();
		~BeppiPh2Body();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mBodyAnimator;
		Animator* mLeftPipeAnimator;
		Animator* mRightPipeAnimator;
		Animator* mLeftBottleAnimator;
		Animator* mRightBottleAnimator;
		Animator* mTankAnimator;
	};
}
