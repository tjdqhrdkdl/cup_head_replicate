#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class WinObjects : public GameObject
	{
	public:
		WinObjects();
		~WinObjects();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Circle();
	private:
		Animator* mCupheadAnimator;
		Animator* mBoardAnimator;
		Animator* mTitleAnimator;
		Animator* mCircleAnimator;
	};
}
