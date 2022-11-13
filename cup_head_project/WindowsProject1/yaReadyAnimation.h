#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	
	class Animator;
	class ReadyAnimation : public GameObject
	{
	public:
		ReadyAnimation();
		~ReadyAnimation();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
	private:
		Animator* mAnimator;
	};
}