#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaObjectManager.h"
namespace ya
{
	class Animator;
	class SpecialAttackEffect : public GameObject
	{
	public:
		SpecialAttackEffect(Vector2 dir);
		~SpecialAttackEffect();
		Animator* GetAnimator() { return mAnimator; }
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		void EffectCompleteEvent();
	private:
		Animator* mAnimator;
		Vector2 mDir;
	};
}
