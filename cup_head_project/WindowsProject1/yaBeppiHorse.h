#pragma once
#include "yaGameObject.h"

namespace ya 
{
	class Animator;
	class BeppiHorse:public GameObject
	{
	public:
		BeppiHorse();
		~BeppiHorse();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		Animator* GetHeadAnimator() { return mHeadAnimator; }
		Animator* GetBodyAnimator() { return mBodyAnimator; }
		void SetLighten(bool light);

		void AttackCompleteEvent();

		void ChoiceYellow(bool y) { mbYellow = y; }
		void ChoiceRight(bool r) { mbRight = r , mbDirChanged = true; }

	private:
		Animator* mBodyAnimator;
		Animator* mHeadAnimator;

		bool mbYellow;
		bool mbDirChanged;
		bool mbRight;
	};
}
