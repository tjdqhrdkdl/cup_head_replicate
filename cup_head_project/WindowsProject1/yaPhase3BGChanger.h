#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Phase3BGChanger : public GameObject
	{
	public:
		Phase3BGChanger();
		~Phase3BGChanger();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Phase3BGChangerCompleteEvent();

		void Release();
	private:
		Animator* mAnimator;
		float mTime;
	};
}
