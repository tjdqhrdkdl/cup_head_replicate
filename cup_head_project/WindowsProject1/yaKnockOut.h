#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class KnockOut : public GameObject
	{
	public:
		KnockOut();
		~KnockOut();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void KnockOutCompleteEvent();

	private:
		Animator* mAnimator;
		float mTime;
	};
}
