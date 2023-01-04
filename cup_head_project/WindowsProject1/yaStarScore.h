#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Number : public GameObject
	{
	public:
		Number();
		~Number();
		Animator* GetAnimator() { return mAnimator; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Animator* mAnimator;
	};
}
