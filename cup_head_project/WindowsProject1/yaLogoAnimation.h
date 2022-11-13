#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya 
{
	class Animator;
	class LogoAnimation : public GameObject
	{
	public:
		LogoAnimation();
		~LogoAnimation();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
	private:
		Animator* mAnimator;
		float mTime;
	};
}
