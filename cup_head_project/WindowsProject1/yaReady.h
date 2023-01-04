#pragma once
#include "Common.h"
#include "yaGameObject.h"

namespace ya
{
	class Animator;
	class Sound;
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
		Sound* mSound1;
		Sound* mSound2;
		Sound* mSoundBell;

		float mTime;
	};
}
