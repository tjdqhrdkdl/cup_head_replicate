#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya 
{
	class Animator;
	class LogoObject : public GameObject
	{
	public:
		LogoObject();
		~LogoObject();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
	private:
		Animator* mAnimator;
	};
}
