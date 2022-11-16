#pragma once
#include "Common.h"
#include "yaGameObject.h"
#include "yaPicture.h"

namespace ya 
{

	class Animator;
	class BeppiPhaseOne : public GameObject
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
		void OnHitCheck();
		void Move();

		void AttackStartCompleteEvent();
		void AttackSmashCompleteEvent();
		void IdleCompleteEvent();
		void EndCompleteEvent();

		virtual void OnCollisonEnter(Collider* other) override;
		virtual void OnCollisonStay(Collider* other) override;
		virtual void OnCollisonExit(Collider* other) override;
	private:
		float mIdleSpeed;
		float mAttackSpeed;
		float mHp;

		Animator* mAnimator;
		bool onHit;
		float onHitChecker;

		float mAttackTimeChecker;
		float mIdleMoveTimeChecker;

		int mCurState;

	};
}
