#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Ready : public GameObject
	{
	public:
		Ready();
		~Ready();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void ReadyCompleteEvent();

	private:
		Animator* mAnimator;
		float mTime;
	};
}
