#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaObjectManager.h"
namespace ya
{
	class Animator;
	class DashEffect : public GameObject
	{
	public:
		DashEffect(bool left = false);
		~DashEffect();
		Animator* GetAnimator() { return mAnimator; }

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		void EffectCompleteEvent();
	private:
		Animator* mAnimator;
		bool isLeft;
	};
}
