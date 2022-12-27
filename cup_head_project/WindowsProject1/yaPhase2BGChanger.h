#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Phase2BGChanger : public GameObject
	{
	public:
		Phase2BGChanger();
		~Phase2BGChanger();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void DestroyGround();

		void Phase2BGChangerCompleteEvent();

		void Release();
	private:
		Animator* mAnimator;
		float mTime;

		GameObject* mPh2WallGround;
	};
}
