#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaFrontUmbrella.h"
namespace ya
{

	class Collider;
	class BeppiPhaseFour : public Monster
	{
	public:
		BeppiPhaseFour(bool init = false);
		~BeppiPhaseFour();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Move();
		void SummonCoaster();
		void SummonPenguin();
		void SummonSwing();
		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void AttackIntroCompleteEvent();
		void AttackFinCompleteEvent();

		void Release();
	private:
		Animator* mLightAnimator;
		Animator* mFrUmbrellaAnimator;
		Animator* mBkUmbrellaAnimator;
		Collider* mCollider;

		FrontUmbrella* mFrUmbrella;

		bool mbIntro;
		bool mbSpitting;

		float mCoasterTimeChecker;
		float mCoasterTime;
		float mSpitTime;
		float mSpitTimeChecker;
		float mPenguinTimeChecker;
		float mPenguinTime;
		float mSwingTime;
		float mSwingTimeChecker;
		float mSwingFirstTimeChecker;

		float mDeathEffectTimeChecker;
		UINT mPenguinCount;
		std::vector<UINT> mPenguinPosArr;

		bool mbFirstSummon;

	};
}
