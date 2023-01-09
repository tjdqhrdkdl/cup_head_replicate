#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaPicture.h"

namespace ya
{

	class Animator;
	class WernerWermanPh1 : public Monster
	{
	public:

		WernerWermanPh1();
		~WernerWermanPh1();
		enum class eWernerWermanAttacks
		{
			Mouse_attack_cannon,
			Mouse_attack_catapult,
			Mouse_attack_dash,
			None
		};	
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		bool IsDashing() { return mbDashIng; }

		void ChoiceAttack();
		void Move();
		void Dash();
		void Cannon();
		void Catapult();
		void SummonSpring();
		void End();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		
		void MouseIntroCompleteEvent();
		void CanContentChangeCompleteEvent();
		void MousePopOutCompleteEvent();
		void MouseShakeFistCompleteEvent();
		void DashStartCompleteEvent();
		void DashStopCopmleteEvent();

		void CannonEnterCompleteEvent();
		void CannonShootCompleteEvent();
		void CannonExitCompleteEvent();
		void CatapultThrowBackCompleteEvent();
		void CatapultThrowGoCompleteEvent();
		void EndArrowCompleteEvent();
		void CanBoomCompleteEvent();

		void Release();

	private:
		Animator* mContentAnimator;
		Animator* mCanFrontAnimator;
		Animator* mCanBackAnimator;
		Animator* mWheelsAnimator;

		bool mbIdleMoving;
		bool mbIdleGoBack;
		bool mbAccelerating;

		bool mbChoiceAttack;
		bool mbMouseDown;
		bool mbLookRight;

		bool mbDashIng;
		bool mbSummonedSpring;
		bool mbDashFin;

		bool mbCannonMode;
		UCHAR mCannonShootCount;

		bool mbCatapultMode;
		bool mbCatapultCharge;
		bool mbCatapultIntroFin;
		bool mbCatapultShooting;
		bool mbCatapultExit;
		UCHAR mCatapultShootCount;

		bool mbEnd;

		float mChoiceTime;
		float mCatapultShootTimeChecker;
		float mCatapultChargeTimeChecker;
		float mCannonShootTimeChecker;
		float mDashTimeChecker;
		float mSpeed;
		eWernerWermanAttacks mBeforeAttack;
		eWernerWermanAttacks mNowAttack;

		UINT mPatternNum;
	};
}
