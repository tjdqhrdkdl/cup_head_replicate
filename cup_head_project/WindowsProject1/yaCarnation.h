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

		virtual void OnCollisonEnter(Collider* other, Collider* my) override;
		virtual void OnCollisonStay(Collider* other, Collider* my) override;
		virtual void OnCollisonExit(Collider* other, Collider* my) override;

		void IntroCompleteEvent();
		void FaceAttackStartCompleteEvent();
		void FaceAttackShootCompleteEvent();
		void FaceAttackComebackCompleteEvent();
		void SeedFireStartCompleteEvent();
		void SeedFireComebackCompleteEvent();
		
		void Release();

	private:
		Collider* mHeadCollider;
		Collider* mBodyCollider;
		float mAttackChoiceTimeChecker;
		float mFaceAttackChargeTimeChecker;
		float mFaceAttackIdleTimeChecker;
		float mFiringSeedIdleTimeChecker;
		eCarnationAttacks mCurAttack;
	};
}
