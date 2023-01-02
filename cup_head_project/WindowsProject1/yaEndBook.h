#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Picture;
	class EndBook : public GameObject
	{
	public:
		EndBook();
		~EndBook();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void PageTurnCompleteEvent();
		void EndCompleteEvent();

	private:
		Animator* mAnimator;
		Animator* mArrowAnimator;

		bool mbArrowMoveRight;
		UINT mPage;
	};
}