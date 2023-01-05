#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class StarScore : public GameObject
	{
	public:
		StarScore();
		~StarScore();
		Animator* GetAnimator() { return mAnimator; }

		void playsound();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		Sound* mSound;
		Animator* mAnimator;
	};
}
