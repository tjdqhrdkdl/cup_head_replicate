#pragma once
#include "yaGameObject.h"

namespace ya 
{

	class Animator;
	class ShootEffect : public GameObject
	{
	public:
		ShootEffect();
		~ShootEffect();
		Animator* GetAnimator() { return mAnimator; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		void ShootEffectCompleteEvent();
	private:
		Animator* mAnimator;
	};
}
