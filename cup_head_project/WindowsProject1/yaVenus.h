#pragma once
#include "Common.h"
#include "yaMonster.h"

namespace ya
{

	class Venus : public Monster
	{
	public:
		Venus();
		~Venus();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void ArriveCompleteEvent();
		void GroundBurstCompleteEvent();
		void VineGrowCompleteEvent();
		void VineReverseCompleteEvent();
		void IntroCompleteEvent();
		void AttackCompleteEvent();

		void DeathCompleteEvent();


		void Release();

	private:
		float mAliveTimeChecker;
		Collider* mCollider;
		Animator* mVineAnimator;
		float mSpeed;
		
		Vector2 mDestDir;
		bool mbIsSeed;

	};
}
