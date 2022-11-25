#pragma once
#include "yaGameObject.h"
#include "yaObjectManager.h"
namespace ya
{
	class Animator;
	class OnHitEffect : public GameObject
	{
	public:
		OnHitEffect();
		~OnHitEffect();
		Animator* GetAnimator() { return mAnimator; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void EffectCompleteEvent();
	private:
		Animator* mAnimator;
	};
}
