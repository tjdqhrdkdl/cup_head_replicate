#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaObjectManager.h"
namespace ya
{
	class Animator;
	class ParryEffect : public GameObject
	{
	public:
		ParryEffect();
		~ParryEffect();
		Animator* GetAnimator() { return mAnimator; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		void EffectCompleteEvent();
	private:
		Animator* mAnimator;
	};
}
