#include "yaCarnation.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaChomper.h"

namespace ya
{
	Carnation::Carnation()
		:mCurAttack(eCarnationAttacks::None)
		, mAttackChoiceTimeChecker(0)
	{
		SetName(L"Carnation");
		mHp = 200;
		SetPos({ 1400,800 });
		SetScale({ 200.0f,350.0f });
		mHeadCollider = new Collider();
		mBodyCollider = new Collider();
		mHeadCollider->SetScale({ 400,400 });
		mHeadCollider->SetAddPos({ 0,-400 });
		mBodyCollider->SetScale({ 200,400 });
		mBodyCollider->SetAddPos({ 0,0 });
		AddComponent(mHeadCollider);
		AddComponent(mBodyCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mMissileAnimator = new Animator();
		AddComponent(mMissileAnimator);

		mMissileAnimator->CreateAnimation(L"MissileFX", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seed Missiles\\flower_gatling_fx_00", 12, 0.05f, false, false);
		mMissileAnimator->SetAddPos({ -70,-670 });


		mAnimator->CreateAnimation(L"Intro", L"..\\Resources\\Image\\Cagney Carnation\\Intro\\Intro_", 21, 0.05f, false, false);
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Cagney Carnation\\Idle\\Idle_", 19, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenIdle", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Idle\\Idle_", 19, 0.05f, false, false));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FiringSeedStart", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Start\\FS_", 7, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFiringSeedStart", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Start\\FS_", 7, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FiringSeedIdle", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Idle\\FS_", 8, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFiringSeedIdle", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Idle\\FS_", 8, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FiringSeedComeback", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Comeback\\FS_", 10, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFiringSeedComeback", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Comeback\\FS_", 10, 0.05f, false, false));

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackHighStart", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\High\\Start\\FA_High_", 5, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFaceAttackHighStart", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\High\\Start\\FA_High_", 5, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackHighCharging", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\High\\Charging\\FA_High_", 3, 0.1f, false, false)
			, mAnimator->CreateAnimation(L"LightenFaceAttackHighCharging", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\High\\Charging\\FA_High_", 3, 0.1f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackHighShoot", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\High\\Shoot\\FA_High_", 5, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFaceAttackHighShoot", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\High\\Shoot\\FA_High_", 5, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackHighIdle", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\High\\Idle\\FA_High_", 5, 0.05f, false, false,{-550,0})
			, mAnimator->CreateAnimation(L"LightenFaceAttackHighIdle", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\High\\Idle\\FA_High_", 5, 0.05f, false, false, { -550,0 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackHighComeback", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\High\\Comeback\\FA_High_", 6, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFaceAttackHighComeback", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\High\\Comeback\\FA_High_", 6, 0.05f, false, false));


		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackLowStart", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\Low\\Start\\FA_Low_", 5, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFaceAttackLowStart", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\Low\\Start\\FA_Low_", 5, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackLowCharging", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\Low\\Charging\\FA_Low_", 3, 0.1f, false, false)
			, mAnimator->CreateAnimation(L"LightenFaceAttackLowCharging", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\Low\\Charging\\FA_Low_", 3, 0.1f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackLowShoot", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\Low\\Shoot\\FA_Low_", 6, 0.05f, false, false,{0,130})
			, mAnimator->CreateAnimation(L"LightenFaceAttackLowShoot", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\Low\\Shoot\\FA_Low_", 6, 0.05f, false, false, { 0,130 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackLowIdle", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\Low\\Idle\\FA_Low_", 5, 0.05f, false, false, { -550,80 })
			, mAnimator->CreateAnimation(L"LightenFaceAttackLowIdle", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\Low\\Idle\\FA_Low_", 5, 0.05f, false, false, { -550,80 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FaceAttackLowComeback", L"..\\Resources\\Image\\Cagney Carnation\\Face Attack\\Low\\Comeback\\FA_Low_", 6, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFaceAttackLowComeback", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Face Attack\\Low\\Comeback\\FA_Low_", 6, 0.05f, false, false));


		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"CreatingObject", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Create_", 28, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenCreatingObject", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Creating Object\\Create_", 28, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FinalIntro", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Intro\\Final_Intro_", 29, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFinalIntro", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Final Form\\Intro\\Final_Intro_", 29, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FinalIdle", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Final_Idle_", 19, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFinalIdle", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Final Form\\Final_Idle_", 19, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FiringPollen", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Firing Pollen\\FP_", 23, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenFiringPollen", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Final Form\\Firing Pollen\\FP_", 23, 0.05f, false, false));

		mAnimator->GetCompleteEvent(L"Intro") = std::bind(&Carnation::IntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighStart") = std::bind(&Carnation::FaceAttackStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowStart") = std::bind(&Carnation::FaceAttackStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighShoot") = std::bind(&Carnation::FaceAttackShootCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowShoot") = std::bind(&Carnation::FaceAttackShootCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighComeback") = std::bind(&Carnation::FaceAttackComebackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowComeback") = std::bind(&Carnation::FaceAttackComebackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FiringSeedStart") = std::bind(&Carnation::SeedFireStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FiringSeedComeback") = std::bind(&Carnation::SeedFireComebackCompleteEvent, this);

		mAnimator->Play(L"Intro", false);
	}

	Carnation::~Carnation()
	{
	}

	void Carnation::Tick()
	{
		Monster::Tick();
		if (mAnimator->GetPlayAnimation()->GetName() != L"Intro")
		{
			ChoiceAttack();
			FaceAttack();
			SeedFire();
		}
	}

	void Carnation::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void Carnation::ChoiceAttack()
	{
		if (mCurAttack == eCarnationAttacks::None)
		{
			mAttackChoiceTimeChecker += Time::DeltaTime();
			if (mAttackChoiceTimeChecker > 3)
			{
				switch (rand()%3)
				{
				case 0:
					mAnimator->Play(L"FaceAttackHighStart", false);
					mCurAttack = eCarnationAttacks::Carnation_FaceAttack_High;
					break;
				case 1:
					mAnimator->Play(L"FaceAttackLowStart", false);
					mCurAttack = eCarnationAttacks::Carnation_FaceAttack_Low;
					break;
				case 2:
					mAnimator->Play(L"FiringSeedStart", false);
					mCurAttack = eCarnationAttacks::Carnation_FiringSeed;

				}
				mAttackChoiceTimeChecker = 0;
			}
		}
	}

	void Carnation::FaceAttack()
	{
		if (mAnimator->GetPlayAnimation()->GetName() == L"FaceAttackHighCharging"
			|| mAnimator->GetPlayAnimation()->GetName() == L"FaceAttackLowCharging")
		{
			mFaceAttackChargeTimeChecker += Time::DeltaTime();
			if (mFaceAttackChargeTimeChecker > 1)
			{
				mFaceAttackChargeTimeChecker = 0;
				if (mCurAttack == eCarnationAttacks::Carnation_FaceAttack_High)
					mAnimator->Play(L"FaceAttackHighShoot", false);
				else
					mAnimator->Play(L"FaceAttackLowShoot", false);
			}
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"FaceAttackHighIdle"
			|| mAnimator->GetPlayAnimation()->GetName() == L"FaceAttackLowIdle")
		{
			mFaceAttackIdleTimeChecker += Time::DeltaTime();
			if (mFaceAttackIdleTimeChecker > 1)
			{
				mFaceAttackIdleTimeChecker = 0;
				if (mCurAttack == eCarnationAttacks::Carnation_FaceAttack_High)
					mAnimator->Play(L"FaceAttackHighComeback", false);
				else
					mAnimator->Play(L"FaceAttackLowComeback", false);
				mHeadCollider->SetScale({ 400,400 });
				mHeadCollider->SetAddPos({ 0,-400 });

			}
		}
	}

	void Carnation::SeedFire()
	{
		if (mAnimator->GetPlayAnimation()->GetName() == L"FiringSeedIdle")
		{
			mFiringSeedIdleTimeChecker += Time::DeltaTime();
			mChomperSummonTimeChecker += Time::DeltaTime();
			if (mFiringSeedIdleTimeChecker > 5)
			{
				mFiringSeedIdleTimeChecker = 0;
				mAnimator->Play(L"FiringSeedComeback", false);
				mMissileAnimator->SetPlayAnimation(nullptr);
			}

			if (mChomperSummonTimeChecker > 1.5f)
			{
				mChomperSummonTimeChecker = 0;
				Chomper* seed = ObjectManager::Instantiate<Chomper>(SceneManager::GetCurScene(), eColliderLayer::Monster_Projecttile);
				seed->SetPos({(float)(rand() % 1000) + 100,-100 });
			}
		}
	}

	void Carnation::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
	}

	void Carnation::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Carnation::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Carnation::IntroCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
	}

	void Carnation::FaceAttackStartCompleteEvent()
	{
		if (mCurAttack == eCarnationAttacks::Carnation_FaceAttack_High)
		{
			mAnimator->Play(L"FaceAttackHighCharging", true);
		}
		else
		{
			mAnimator->Play(L"FaceAttackLowCharging", true);
			mHeadCollider->SetAddPos({ 0,0 });
		}

	}

	void Carnation::FaceAttackShootCompleteEvent()
	{
		if (mCurAttack == eCarnationAttacks::Carnation_FaceAttack_High)
		{
			mAnimator->Play(L"FaceAttackHighIdle", true);
			mHeadCollider->SetAddPos({ -600,-400 });
			mHeadCollider->SetScale({ 1600,400 });
		}
		else
		{
			mAnimator->Play(L"FaceAttackLowIdle", true);
			mHeadCollider->SetAddPos({ -600,100 });
			mHeadCollider->SetScale({ 1600,300 });
		}

	}

	void Carnation::FaceAttackComebackCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
		mCurAttack = eCarnationAttacks::None;
	}

	void Carnation::SeedFireStartCompleteEvent()
	{
		mAnimator->Play(L"FiringSeedIdle", true);
		mMissileAnimator->Play(L"MissileFX", true);
	}

	void Carnation::SeedFireComebackCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
		mCurAttack = eCarnationAttacks::None;
	}

	void Carnation::Release()
	{
		mAnimator->Release();
	}

}