#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaPicture.h"
#include "yaBottomWoodCart.h"
#include "yaDisc.h"
namespace ya
{

	class Animator;
	class Collider;
	class WernerWermanPh2 : public Monster
	{
	public:

		WernerWermanPh2(bool right, bool init = false);
		~WernerWermanPh2();


		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Scissor();
		void Fire();
		void ChoiceDisc();
		void Move();

		void DestroyWoodCart();
		void SetDiscs(Disc* disc, int i);

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;


		void MouseIntroCompleteEvent();
		void TransitionEnterCompleteEvent();
		void ScissorMoveCompleteEvent();
		void FireCompleteEvent();

		void Release();

	private:
		BottomWoodCart* mWoodCart;
		std::vector<Disc*> mDiscs[2];

		Animator* mBottomAnimator;
		Animator* mTinBackAnimator;
		Animator* mScissorAnimator;
		Animator* mLeftCannonAnimator;
		Animator* mRightCannonAnimator;
		Animator* mMouseAnimator;
		Animator* mTinFrontAnimator;
		Animator* mLeftFireAnimator;
		Animator* mRightFireAnimator;

		Collider* mCollider;
		Collider* mHeadCollider;
		Collider* mFireLeftSmallCollider;
		Collider* mFireLeftLargeCollider;
		Collider* mFireRightSmallCollider;
		Collider* mFireRightLargeCollider;

		bool mbRight;
		bool mbScissorMove;
		bool mbSpeedUp;
		bool mbDead;

		float mScissorMoveTimeChecker;
		float mBeforeScissorHeight;
		float mFireTimeChecker;
		float mDiscTimeChecker;
		float mSpeed;
		float mDeathTimeChecker;
	};
}
