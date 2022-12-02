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

		void IntroCue1();
		void IntroCue2();

		void PipeIntroCompleteEvent();
	private:
		bool mIntroMove;
		Vector2 mVelocity;
		Animator* mBodyAnimator;
		Animator* mLeftPipeAnimator;
		Animator* mRightPipeAnimator;
		Animator* mLeftBottleAnimator;
		Animator* mRightBottleAnimator;
		Animator* mTankAnimator;
	};
}
