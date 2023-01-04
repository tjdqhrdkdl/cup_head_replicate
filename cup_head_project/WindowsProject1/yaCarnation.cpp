#include "yaCarnation.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaChomper.h"
#include "yaMiniFlower.h"
#include "yaVenus.h"
#include "yaAcorn.h"
#include "yaBoomerang.h"
#include "yaPollen.h"
#include "yaBossExplosion.h"
#include "yaKnockOut.h"
#include "yaBossCarnationScene.h"
namespace ya
{
	Carnation::Carnation()
		:mCurAttack(eCarnationAttacks::None)
		, mAttackChoiceTimeChecker(0)
	{
		SetName(L"Carnation");
		mHp = 201;
		SetPos({ 1400,800 });
		SetScale({ 200.0f,350.0f });
		mHeadCollider = new Collider();
		mBodyCollider = new Collider();
		mFinalVineMainCollider = new Collider();
		mFinalVineACollider = new Collider();
		mFinalVineBCollider = new Collider();
		mFinalVineCCollider = new Collider();
		mFinalVineMainCollider->SetBulletPassing(true);
		mFinalVineACollider->SetBulletPassing(true);
		mFinalVineBCollider->SetBulletPassing(true);
		mFinalVineCCollider->SetBulletPassing(true);
		mFinalVineMainCollider->SetOff(true);
		mFinalVineACollider->SetOff(true);
		mFinalVineBCollider->SetOff(true);
		mFinalVineCCollider->SetOff(true);

		mHeadCollider->SetScale({ 300,400 });
		mHeadCollider->SetAddPos({ 0,-400 });
		mBodyCollider->SetScale({ 200,400 });
		mBodyCollider->SetAddPos({ 0,0 });
		mFinalVineMainCollider->SetScale({ 1600,100 });
		mFinalVineMainCollider->SetAddPos({ -800,170 });
		mFinalVineACollider->SetScale({ 150,600 });
		mFinalVineBCollider->SetScale({ 150,600 });
		mFinalVineCCollider->SetScale({ 150,600 });
		mFinalVineACollider->SetAddPos({ -450,0 });
		mFinalVineBCollider->SetAddPos({ -810,0 });
		mFinalVineCCollider->SetAddPos({ -1170,0 });
		AddComponent(mHeadCollider);
		AddComponent(mBodyCollider);
		AddComponent(mFinalVineMainCollider);
		AddComponent(mFinalVineACollider);
		AddComponent(mFinalVineBCollider);
		AddComponent(mFinalVineCCollider);

		mAnimator = new Animator();
		mMissileAnimator = new Animator();
		mFinalVineMainAnimator = new Animator();
		mFinalVineAAnimator = new Animator();
		mFinalVineBAnimator = new Animator();
		mFinalVineCAnimator = new Animator();

		AddComponent(mAnimator);
		AddComponent(mFinalVineMainAnimator);
		AddComponent(mFinalVineAAnimator);
		AddComponent(mFinalVineBAnimator);
		AddComponent(mFinalVineCAnimator);
		AddComponent(mMissileAnimator);
		mFinalVineMainAnimator->SetAddPos({ -900,-10 });
		mFinalVineAAnimator->SetAddPos({ -450,10 });
		mFinalVineBAnimator->SetAddPos({ -810,10 });
		mFinalVineCAnimator->SetAddPos({ -1170,10 });

		mFinalVineMainAnimator->CreateAnimation(L"FinalVineMain", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Main\\Vine_Main_", 24, 0.06f, false, false);
		mFinalVineAAnimator->CreateAnimation(L"Ready", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Ready\\Vine_Platform_A_", 11, 0.05f, false, false);
		mFinalVineAAnimator->CreateAnimation(L"Go", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Go\\Vine_Platform_A_", 12, 0.05f, false, false);
		mFinalVineAAnimator->CreateAnimation(L"Comeback", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Comeback\\Vine_Platform_A_", 22, 0.04f, false, false);
		mFinalVineBAnimator->CreateAnimation(L"Ready", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Ready\\Vine_Platform_A_", 11, 0.05f, false, false);
		mFinalVineBAnimator->CreateAnimation(L"Go", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Go\\Vine_Platform_A_", 12, 0.05f, false, false);
		mFinalVineBAnimator->CreateAnimation(L"Comeback", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Comeback\\Vine_Platform_A_", 22, 0.04f, false, false);
		mFinalVineCAnimator->CreateAnimation(L"Ready", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Ready\\Vine_Platform_A_", 11, 0.05f, false, false);
		mFinalVineCAnimator->CreateAnimation(L"Go", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Go\\Vine_Platform_A_", 12, 0.05f, false, false);
		mFinalVineCAnimator->CreateAnimation(L"Comeback", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Vines\\Comeback\\Vine_Platform_A_", 22, 0.04f, false, false);

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


		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"CreatingObjectIntro", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Intro\\Create_", 12, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenCreatingObjectIntro", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Creating Object\\Intro\\Create_", 12, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"CreatingObjectCharge", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Charging\\Create_", 3, 0.1f, false, false)
			, mAnimator->CreateAnimation(L"LightenCreatingObjectCharge", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Creating Object\\Charging\\Create_", 3, 0.1f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"CreatingObjectShoot", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Shoot\\Create_", 6, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenCreatingObjectShoot", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Creating Object\\Shoot\\Create_", 6, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"CreatingObjectIdle", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Idle\\Create_", 3, 0.1f, false, false)
			, mAnimator->CreateAnimation(L"LightenCreatingObjectIdle", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Creating Object\\Idle\\Create_", 3, 0.1f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"CreatingObjectComeback", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Comeback\\Create_", 7, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenCreatingObjectComeback", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Creating Object\\Comeback\\Create_", 7, 0.05f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"CreatingObjectFin", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Fin\\Create_0", 12, 0.05f, false, false)
			, mAnimator->CreateAnimation(L"LightenCreatingObjectFin", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Creating Object\\Fin\\Create_0", 12, 0.05f, false, false));


		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FinalIntro", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Intro\\Final_Intro_", 29, 0.05f, false, false,{0,50})
			, mAnimator->CreateAnimation(L"LightenFinalIntro", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Final Form\\Intro\\Final_Intro_", 29, 0.05f, false, false, { 0,50 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FinalIdle", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Final_Idle_", 19, 0.05f, false, false, { 0,75 })
			, mAnimator->CreateAnimation(L"LightenFinalIdle", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Final Form\\Final_Idle_", 19, 0.05f, false, false, { 0,75 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"FiringPollen", L"..\\Resources\\Image\\Cagney Carnation\\Final Form\\Firing Pollen\\FP_", 23, 0.05f, false, false, { 0,75 })
			, mAnimator->CreateAnimation(L"LightenFiringPollen", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Final Form\\Firing Pollen\\FP_", 23, 0.05f, false, false, { 0,75 }));

		mAnimator->CreateAnimation(L"Death", L"..\\Resources\\Image\\Cagney Carnation\\Death\\Death_", 13, 0.05f, false, false, { 0,75 });

		mAnimator->GetCompleteEvent(L"Intro") = std::bind(&Carnation::IntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighStart") = std::bind(&Carnation::FaceAttackStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowStart") = std::bind(&Carnation::FaceAttackStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighShoot") = std::bind(&Carnation::FaceAttackShootCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowShoot") = std::bind(&Carnation::FaceAttackShootCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackHighComeback") = std::bind(&Carnation::FaceAttackComebackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FaceAttackLowComeback") = std::bind(&Carnation::FaceAttackComebackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FiringSeedStart") = std::bind(&Carnation::SeedFireStartCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FiringSeedComeback") = std::bind(&Carnation::SeedFireComebackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CreatingObjectIntro") = std::bind(&Carnation::CreatingObjectIntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CreatingObjectShoot") = std::bind(&Carnation::CreatingObjectShootCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CreatingObjectComeback") = std::bind(&Carnation::CreatingObjectComebackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"CreatingObjectFin") = std::bind(&Carnation::CreatingObjectFinCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FinalIntro") = std::bind(&Carnation::FinalIntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"FiringPollen") = std::bind(&Carnation::FiringPollenCompleteEvent, this);

		mFinalVineMainAnimator->GetCompleteEvent(L"FinalVineMain") = std::bind(&Carnation::FinalVineMainCompleteEvent, this);

		mFinalVineAAnimator->GetCompleteEvent(L"Ready") = std::bind(&Carnation::FinalVineAReadyCompleteEvent, this);
		mFinalVineAAnimator->GetCompleteEvent(L"Go") = std::bind(&Carnation::FinalVineAGoCompleteEvent, this);
		mFinalVineAAnimator->GetCompleteEvent(L"Comeback") = std::bind(&Carnation::FinalVineAComebackCompleteEvent, this);
		mFinalVineBAnimator->GetCompleteEvent(L"Ready") = std::bind(&Carnation::FinalVineBReadyCompleteEvent, this);
		mFinalVineBAnimator->GetCompleteEvent(L"Go") = std::bind(&Carnation::FinalVineBGoCompleteEvent, this);
		mFinalVineBAnimator->GetCompleteEvent(L"Comeback") = std::bind(&Carnation::FinalVineBComebackCompleteEvent, this);
		mFinalVineCAnimator->GetCompleteEvent(L"Ready") = std::bind(&Carnation::FinalVineCReadyCompleteEvent, this);
		mFinalVineCAnimator->GetCompleteEvent(L"Go") = std::bind(&Carnation::FinalVineCGoCompleteEvent, this);
		mFinalVineCAnimator->GetCompleteEvent(L"Comeback") = std::bind(&Carnation::FinalVineCComebackCompleteEvent, this);


		mAnimator->Play(L"Intro", false);

		//init
		Chomper();
		MiniFlower();
		Venus();
		Acorn();
		Boomerang();
		Pollen();
	}

	Carnation::~Carnation()
	{
	}

	void Carnation::Tick()
	{
		Monster::Tick();
		if (mAnimator->GetPlayAnimation()->GetName() != L"Death")
		{
			if (mAnimator->GetPlayAnimation()->GetName() != L"Intro"
				&& !mbFinalForm)
			{
				ChoiceAttack();
				FaceAttack();
				SeedFire();
				CreateObject();

				if (mHp < 200 && mAnimator->GetPlayAnimation()->GetName() == L"Idle")
				{
					mbFinalForm = true;		
					mHeadCollider->SetScale({ 300,300 });
					mHeadCollider->SetAddPos({ 0,-300 });
					mAnimator->Play(L"FinalIntro", false);
				}
			}

			else if (mbFinalForm && mAnimator->GetPlayAnimation()->GetName() != L"FinalIntro")
			{
				VineAttack();
				SummonPollen();
				if (mHp < 0)
				{
					mAnimator->Play(L"Death", true);
					dynamic_cast<BossCarnationScene*>(SceneManager::GetCurScene())->BGMOff();
					ObjectManager::Instantiate<KnockOut>(SceneManager::GetCurScene(), eColliderLayer::UI);
					mHeadCollider->SetOff(true);
					mBodyCollider->SetOff(true);
					mFinalVineMainCollider->SetOff(true);
					ObjectManager::Destroy(this, 300.0f);

				}
			}
		}

		else
		{
			mDeathEffectTimeChecker += Time::DeltaTime();
			if (mDeathEffectTimeChecker > 0.4f + (rand() % 5) * 0.1)
			{
				mDeathEffectTimeChecker = 0;
				Vector2 pos = { 1400,650 };
				switch (rand() % 6)
				{
				case 0:
					pos += {160, 120};
					break;
				case 1:
					pos += {-250, 30};
					break;
				case 2:
					pos += {200, 50};
					break;
				case 3:
					pos += {-20, 250};
					break;
				case 4:
					pos += {-170, 40};
					break;
				case 5:
					pos += {60, 200};
					break;
				}

				BossExplosion* effect = ObjectManager::Instantiate<BossExplosion>(SceneManager::GetCurScene(), eColliderLayer::Effect);
				if (soundPlay == false)
				{
					soundPlay = true;
					effect->SoundPlay();
				}
				effect->SetPos(pos);
			}
			if (GetDeathTime() < 295)
				dynamic_cast<BossCarnationScene*>(SceneManager::GetCurScene())->SetPhase(5);
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
				switch (rand()%4)
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
					break;
				case 3:
					mAnimator->Play(L"CreatingObjectIntro", false);
					mCurAttack = eCarnationAttacks::Carnation_CreateObject;
					break;
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
				mHeadCollider->SetScale({ 300,400 });
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
			mMiniFlowerSummonTimeChecker += Time::DeltaTime();
			mVenusSummonTimeChecker += Time::DeltaTime();
			if (mFiringSeedIdleTimeChecker > 5)
			{
				mFiringSeedIdleTimeChecker = 0;
				mChomperSummonTimeChecker = 0;
				mMiniFlowerSummonTimeChecker = 0;
				mVenusSummonTimeChecker = 0;
				mAnimator->Play(L"FiringSeedComeback", false);
				mMissileAnimator->SetPlayAnimation(nullptr);
			}

			if (mChomperSummonTimeChecker > 2.6f)
			{
				mChomperSummonTimeChecker = 0;
				Chomper* seed = ObjectManager::Instantiate<Chomper>(SceneManager::GetCurScene(), eColliderLayer::Monster_Projecttile);
				seed->SetPos({ (float)(rand() % 1000) + 100,-100 });
			}
			if (mMiniFlowerSummonTimeChecker > 4.5f)
			{
				mMiniFlowerSummonTimeChecker = 0;
				MiniFlower* seed = ObjectManager::Instantiate<MiniFlower>(SceneManager::GetCurScene(), eColliderLayer::Monster_Projecttile);
				seed->SetPos({ (float)(rand() % 1000) + 100,-100 });
			}
			if (mVenusSummonTimeChecker > 1.6f)
			{
				mVenusSummonTimeChecker = 0;
				Venus* seed = ObjectManager::Instantiate<Venus>(SceneManager::GetCurScene(), eColliderLayer::Monster_Projecttile);
				seed->SetPos({ (float)(rand() % 1000) + 100,-100 });
			}

		}
	}

	void Carnation::CreateObject()
	{
		if (mAnimator->GetPlayAnimation()->GetName() == L"CreatingObjectCharge")
		{
			mCreateChargeTimeChecker += Time::DeltaTime();
			if (mCreateChargeTimeChecker > 1)
			{
				mCreateChargeTimeChecker = 0;
				mAnimator->Play(L"CreatingObjectShoot", false);
			}
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"CreatingObjectIdle")
		{
			mCreateIdleTimeChecker += Time::DeltaTime();
			if (mCreateCount < 3)
			{
				if (mCreateIdleTimeChecker > 2.5)
				{
					mCreateIdleTimeChecker = 0;
					mAnimator->Play(L"CreatingObjectComeback", false);
				}
			}
			else
			{
				if (mCreateIdleTimeChecker > 1)
				{
					mCreateIdleTimeChecker = 0;
					mAnimator->Play(L"CreatingObjectComeback", false);
				}
			}
		}
	}

	void Carnation::VineAttack()
	{
		mVineAttackTimeChecker += Time::DeltaTime();
		if (mVineAttackTimeChecker > 5)
		{
			mVineAttackTimeChecker = 0;
			switch (rand() % 3)
			{
			case 0:
				mFinalVineAAnimator->Play(L"Ready", false);
				mFinalVineBAnimator->Play(L"Ready", false);
				break;
			case 1:
				mFinalVineCAnimator->Play(L"Ready", false);
				mFinalVineBAnimator->Play(L"Ready", false);
				break;
			case 2:
				mFinalVineAAnimator->Play(L"Ready", false);
				mFinalVineCAnimator->Play(L"Ready", false);
				break;
			}
		}

		if (mVineAReady)
			mVineAGoTimeChecker += Time::DeltaTime();
		if (mVineBReady)
			mVineBGoTimeChecker += Time::DeltaTime();
		if (mVineCReady)
			mVineCGoTimeChecker += Time::DeltaTime();

		if (mVineAGoTimeChecker > 1)
		{
			mVineAReady = false;
			mVineAGoTimeChecker = 0;
			mFinalVineAAnimator->Play(L"Go", false);
			mFinalVineACollider->SetOff(false);
		}
		if (mVineBGoTimeChecker > 1)
		{
			mVineBReady = false;
			mVineBGoTimeChecker = 0;
			mFinalVineBAnimator->Play(L"Go", false);
			mFinalVineBCollider->SetOff(false);

		}
		if (mVineCGoTimeChecker > 1)
		{
			mVineCReady = false;
			mVineCGoTimeChecker = 0;
			mFinalVineCCollider->SetOff(false);
			mFinalVineCAnimator->Play(L"Go", false);
		}
	}

	void Carnation::SummonPollen()
	{
		mPollenTimeChecker += Time::DeltaTime();
		if (mPollenTimeChecker > 5)
		{
			mAnimator->Play(L"FiringPollen", false);
			mPollenTimeChecker = 1.6;
		}

		if (mAnimator->GetPlayAnimation()->GetName() == L"FiringPollen")
		{
			if (mPollenTimeChecker > 2)
			{
				mPollenTimeChecker = 0;
				bool pink = rand() % 2;
				Pollen* pollen = new Pollen(pink);
				pollen->SetPos({ 1150,400 });
				SceneManager::GetCurScene()->AddGameObject(pollen, eColliderLayer::Monster_Projecttile);
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
			mHeadCollider->SetScale({ 4000,200 });
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

	void Carnation::CreatingObjectIntroCompleteEvent()
	{
		mAnimator->Play(L"CreatingObjectCharge", true);
	}

	void Carnation::CreatingObjectShootCompleteEvent()
	{
		mAnimator->Play(L"CreatingObjectIdle", true);
		if (mCreateCount < 2)
		{
			for (size_t i = 0; i < 3; i++)
			{
				Acorn* acorn = ObjectManager::Instantiate<Acorn>(SceneManager::GetCurScene(), eColliderLayer::Monster_Projecttile);
				acorn->SetPos({ 1200, 200.0f + 200 * i });
				acorn->SetShootTime(1 + 0.5 * i);
			}
		}
		else
		{
			Boomerang* boomerang = ObjectManager::Instantiate<Boomerang>(SceneManager::GetCurScene(), eColliderLayer::Monster_Projecttile);
			boomerang->SetPos({ 1200,400 });

		}
		++mCreateCount;
	}

	void Carnation::CreatingObjectComebackCompleteEvent()
	{
		if (mCreateCount > 2)
			mAnimator->Play(L"CreatingObjectFin", false);
		else
			mAnimator->Play(L"CreatingObjectCharge", true);
	}

	void Carnation::CreatingObjectFinCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
		mCurAttack = eCarnationAttacks::None;
		mCreateCount = 0;
	}

	void Carnation::FinalIntroCompleteEvent()
	{
		mAnimator->Play(L"FinalIdle", true);
		mFinalVineMainAnimator->Play(L"FinalVineMain", false);
	}

	void Carnation::FinalVineMainCompleteEvent()
	{
		mFinalVineMainCollider->SetOff(false);
	}

	void Carnation::FinalVineAReadyCompleteEvent()
	{
		mVineAReady = true;
	}

	void Carnation::FinalVineBReadyCompleteEvent()
	{
		mVineBReady = true;

	}

	void Carnation::FinalVineCReadyCompleteEvent()
	{
		mVineCReady = true;

	}

	void Carnation::FinalVineAGoCompleteEvent()
	{
		mFinalVineAAnimator->Play(L"Comeback", false);
		mFinalVineACollider->SetOff(true);
	}

	void Carnation::FinalVineBGoCompleteEvent()
	{
		mFinalVineBAnimator->Play(L"Comeback", false);
		mFinalVineBCollider->SetOff(true);
	}

	void Carnation::FinalVineCGoCompleteEvent()
	{
		mFinalVineCAnimator->Play(L"Comeback", false);
		mFinalVineCCollider->SetOff(true);
	}

	void Carnation::FinalVineAComebackCompleteEvent()
	{
		mFinalVineAAnimator->SetPlayAnimation(nullptr);

	}

	void Carnation::FinalVineBComebackCompleteEvent()
	{
		mFinalVineBAnimator->SetPlayAnimation(nullptr);
	}

	void Carnation::FinalVineCComebackCompleteEvent()
	{
		mFinalVineCAnimator->SetPlayAnimation(nullptr);
	}

	void Carnation::FiringPollenCompleteEvent()
	{
		mAnimator->Play(L"FinalIdle", true);
	}


	void Carnation::Release()
	{
		mAnimator->Release();
		mMissileAnimator->Release();
		mFinalVineMainAnimator->Release();
		mFinalVineAAnimator->Release();
		Chomper().Release();
		MiniFlower().Release();
		Venus().Release();
		Acorn().Release();
		Boomerang().Release();
		Pollen().Release();
	}

}