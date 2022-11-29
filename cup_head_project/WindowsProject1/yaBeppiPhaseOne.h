#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaPicture.h"

namespace ya 
{

	class Animator;
	class BeppiPhaseOne : public Monster
	{
	public:
		enum eBeppiPh1State
		{
			BeppiPh1State_None			 = 0x00000000,
			BeppiPh1State_LookLeft		 = 0x00000001,
			BeppiPh1State_OnAttackStart	 = 0x00000002,
			BeppiPh1State_OnAttackMoving = 0x00000004,
			BeppiPh1State_OnAttackSmash  = 0x00000008,
			BeppiPh1State_OnIdleMove	 = 0x00000010,
			BeppiPh1State_EndFall		 = 0x00000020,
		};
		BeppiPhaseOne();
		~BeppiPhaseOne();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		void SetAnimation();
		void Attack();
		void Move();
		void SummonDuck();

		void AttackStartCompleteEvent();
		void AttackSmashCompleteEvent();
		void IdleCompleteEvent();
		void EndCompleteEvent();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;
	private:
		float mIdleSpeed;
		float mAttackSpeed;
		float mDuckTime;



		float mAttackTimeChecker;
		float mIdleMoveTimeChecker;
		float mDuckTimeChecker;

		int mPinkDuckChecker;
		int mBulbDuckChecker;
		int mCurState;

		bool mAttackStarted;
		float mAttackStartedTimeChecker;

	};
}
