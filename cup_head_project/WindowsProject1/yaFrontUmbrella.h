#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class FrontUmbrella : public GameObject
	{
	public:
		FrontUmbrella();
		~FrontUmbrella();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		Animator* GetAnimator() { return mAnimator; }

		void IntroCompleteEvent();
		
		bool mIntroFin;

		void Release();
	private:
		Animator* mAnimator;
	};
}