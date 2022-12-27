#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Phase3BGExplodeEffect : public GameObject
	{
	public:
		Phase3BGExplodeEffect();
		~Phase3BGExplodeEffect();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Phase3BGExplodeEffectCompleteEvent();

		void Release();
	private:
		Animator* mAnimator;
		float mTime;
	};
}
