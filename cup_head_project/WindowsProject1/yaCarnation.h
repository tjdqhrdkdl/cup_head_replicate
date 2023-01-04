#pragma once
#include "Common.h"
#include "yaMonster.h"
#include "yaPicture.h"

namespace ya
{

	class Carnation : public Monster
	{
	public:

		Carnation();
		~Carnation();
		enum class eCarnationAttacks
		{
			None,
			Carnation_FaceAttack_High,
			Carnation_FaceAttack_Low,
			Carnation_FiringSeed,
			Carnation_CreateObject,
		};
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		
		void ChoiceAttack();
		void FaceAttack();
		void SeedFire();
		void CreateObject();
		void VineAttack();
		void SummonPollen();

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void IntroCompleteEvent();
		void FaceAttackStartCompleteEvent();
		void FaceAttackShootCompleteEvent();
		void FaceAttackComebackCompleteEvent();
		void SeedFireStartCompleteEvent();
		void SeedFireComebackCompleteEvent();
		void CreatingObjectIntroCompleteEvent();
		void CreatingObjectShootCompleteEvent();
		void CreatingObjectComebackCompleteEvent();
		void CreatingObjectFinCompleteEvent();
		void FinalIntroCompleteEvent();
		void FinalVineMainCompleteEvent();
		void FinalVineAReadyCompleteEvent();
		void FinalVineBReadyCompleteEvent();
		void FinalVineCReadyCompleteEvent();
		void FinalVineAGoCompleteEvent();
		void FinalVineBGoCompleteEvent();
		void FinalVineCGoCompleteEvent();
		void FinalVineAComebackCompleteEvent();
		void FinalVineBComebackCompleteEvent();
		void FinalVineCComebackCompleteEvent();
		void FiringPollenCompleteEvent();

		void Release();

	private:
		Collider* mHeadCollider;
		Collider* mBodyCollider;
		Collider* mFinalVineMainCollider;
		Collider* mFinalVineACollider;
		Collider* mFinalVineBCollider;
		Collider* mFinalVineCCollider;

		Animator* mMissileAnimator;
		Animator* mFinalVineMainAnimator;
		Animator* mFinalVineAAnimator;
		Animator* mFinalVineBAnimator;
		Animator* mFinalVineCAnimator;


		float mAttackChoiceTimeChecker;
		float mFaceAttackChargeTimeChecker;
		float mFaceAttackIdleTimeChecker;
		float mFiringSeedIdleTimeChecker;
		float mChomperSummonTimeChecker;
		float mMiniFlowerSummonTimeChecker;
		float mVenusSummonTimeChecker;
		float mCreateChargeTimeChecker;
		float mCreateIdleTimeChecker;

		float mVineAttackTimeChecker;
		float mVineAGoTimeChecker;
		float mVineBGoTimeChecker;
		float mVineCGoTimeChecker;
		float mPollenTimeChecker;

		float mDeathEffectTimeChecker;

		bool mVineAReady;
		bool mVineBReady;
		bool mVineCReady;


		bool mbFinalForm;
		UINT mCreateCount;
		bool soundPlay;
		eCarnationAttacks mCurAttack;
	};
}
