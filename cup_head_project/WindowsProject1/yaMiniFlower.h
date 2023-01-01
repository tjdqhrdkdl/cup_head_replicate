#pragma once
#include "Common.h"
#include "yaMonster.h"

namespace ya
{

	class MiniFlower: public Monster
	{
	public:
		MiniFlower();
		~MiniFlower();

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
		Collider* mCollider;
		Animator* mVineAnimator;
		float mSpeed;
		float mAttackTimeChecker;

		bool mbGoRight;
		bool mbIsSeed;

	};
}
