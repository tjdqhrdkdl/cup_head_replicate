#include "yaBeppiPhaseFour.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaRollerCoaster.h"
#include "yaBossBeppiScene.h"
#include "yaBossExplosion.h"
#include "yaPenguin.h"
#include "yaSwingPlatform.h"
#include "yaKnockOut.h"
#include "yaSound.h"
#include "yaResources.h"
namespace ya
{
	BeppiPhaseFour::BeppiPhaseFour(bool init)
		:mbIntro(true)
		, mCoasterTimeChecker(9)
		, mSpitTimeChecker(5)
		, mPenguinTimeChecker(0)
		, mSwingTimeChecker(0)
		, mSwingFirstTimeChecker(0)
		, mDeathEffectTimeChecker(0)
		, mSpitTime(18)
		, mCoasterTime(18)
		, mPenguinTime(1.3)
		, mSwingTime(1)
	{
		SetName(L"BeppiPhaseFour");
		mHp = 200;
		SetPos({ 800,2500 });
		SetScale({ 260.0f,900.0f });
		mCollider = new Collider();
		AddComponent(mCollider);
		mAnimator = new Animator();
		mLightAnimator = new Animator();
		mBkUmbrellaAnimator = new Animator();
		AddComponent(mBkUmbrellaAnimator);
		AddComponent(mAnimator);
		AddComponent(mLightAnimator);


		mFrUmbrella = new FrontUmbrella();
		mFrUmbrella->SetPos(GetPos());
		if (init)
			;
		else
			SceneManager::GetCurScene()->AddGameObject(mFrUmbrella, eColliderLayer::BehindMonsterHat);
	
		mFrUmbrellaAnimator = mFrUmbrella->GetAnimator();


		mLightAnimator->CreateAnimation(L"LightHatIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Idle\\Lights\\Phase4_Lights_", 6, 0.07f, true, false, {0,-785});
	
		mBkUmbrellaAnimator->CreateAnimation(L"BkUmbrellaIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Umbrella\\Back\\umbrella_bk_00", 13, 0.06f, false, false, { 0,-810 });

		mLightAnimator->Play(L"LightHatIdle", true);
		mFrUmbrellaAnimator->Play(L"FrUmbrellaIntro", false);
		mLightAnimator->SetStop(true);
		mFrUmbrellaAnimator->SetStop(true);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Idle\\Beppi\\Phase4_Idle_", 16, 0.04f, true, false)
			, mAnimator->CreateAnimation(L"LightenIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Idle\\Beppi\\Lighten\\Phase4_Idle_", 16, 0.04f, true, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"AttackIntro", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Attack\\Phase4_Attack_", 19, 0.04f, true, false)
			, mAnimator->CreateAnimation(L"LightenAttackIntro", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Attack\\Lighten\\Phase4_Attack_", 19, 0.04f, true, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"AttackSpit", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Attack\\Spit\\Phase4_Attack_", 6, 0.07f, true, false)
			, mAnimator->CreateAnimation(L"LightenAttackSpit", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Attack\\Lighten\\Spit\\Phase4_Attack_", 6, 0.07f, true, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"AttackFin", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Attack\\Fin\\Phase4_Attack_", 5, 0.08f, true, false)
			, mAnimator->CreateAnimation(L"LightenAttackFin", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Attack\\Lighten\\Fin\\Phase4_Attack_", 5, 0.08f, true, false));

		mAnimator->CreateAnimation(L"End", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\End\\Phase4_End_", 16, 0.05f, true, false);

		mAnimator->GetCompleteEvent(L"AttackIntro") = std::bind(&BeppiPhaseFour::AttackIntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"AttackFin") = std::bind(&BeppiPhaseFour::AttackFinCompleteEvent, this);
		mAnimator->Play(L"Idle", true);

		for (size_t i = 0; i < 6; i++)
		{
			mPenguinPosArr.push_back(i);
		}

		mWarningSound = Resources::Load<Sound>(L"CoasterBell", L"..\\Resources\\Sound\\Clown\\sfx_level_clown_warning_lights_loop_01.wav");
		Penguin(1);
	}

	BeppiPhaseFour::~BeppiPhaseFour()
	{
	}

	void BeppiPhaseFour::Tick()
	{
		Monster::Tick();
		mFrUmbrella->SetPos(GetPos());
		if (mBkUmbrellaAnimator->GetPlayAnimation() == nullptr && mFrUmbrella->mIntroFin)
		{
			mBkUmbrellaAnimator->Play(L"BkUmbrellaIdle", true);
			mbFirstSummon = true;
		}

		if (IsDeathTimeOn() == false)
		{
			SummonCoaster();
			SummonPenguin();
		}
		Move();
		SummonSwing();
		if (mHp < 0)
		{
			if (mAnimator->GetPlayAnimation()->GetName() != L"End")
			{
				ObjectManager::Instantiate<KnockOut>(SceneManager::GetCurScene(), eColliderLayer::UI);
				dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->BGMOff();
				mAnimator->Play(L"End", true);
				ObjectManager::Destroy(this, 300.0f);
			}
			mDeathEffectTimeChecker += Time::DeltaTime();
			if (mDeathEffectTimeChecker > 0.4f + (rand() % 5) * 0.1)
			{
				mDeathEffectTimeChecker = 0;
				Vector2 pos = GetPos();
				pos.y -= 250;
				switch (rand() % 6)
				{
				case 0:
					pos += {60, 120};
					break;
				case 1:
					pos += {-150, 30};
					break;
				case 2:
					pos += {100, 50};
					break;
				case 3:
					pos += {-10, 250};
					break;
				case 4:
					pos += {-70, 40};
					break;
				case 5:
					pos += {100, 200};
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
				dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->SetPhase(5);
		}
	}

	void BeppiPhaseFour::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void BeppiPhaseFour::Move()
	{
		Vector2 pos = GetPos();
		if (mbIntro)
		{
			pos.y -= 300 * Time::DeltaTime();
			if (pos.y <= 1000)
			{
				mbIntro = false;
				mLightAnimator->SetStop(false);
				mFrUmbrellaAnimator->SetStop(false);
				SceneManager::GetCurScene()->ChangeLayer(mFrUmbrella, eColliderLayer::Top_Effect);
				pos.y = 1000;
			}
		}
		SetPos(pos);
	}

	void BeppiPhaseFour::SummonCoaster()
	{
		mCoasterTimeChecker += Time::DeltaTime();
		if (mCoasterTimeChecker > mCoasterTime - 0.6f)
		{
			mWarningSound->Play(false);
		}
		if (mCoasterTimeChecker > mCoasterTime)
		{
			mCoasterTimeChecker = 0;
			RollerCoaster* coaster = new RollerCoaster(10);
			coaster->SetSpeed(1200);
			coaster->Initialize();
			SceneManager::GetCurScene()->AddGameObject(coaster, eColliderLayer::FrontObject);
		}
	}

	void BeppiPhaseFour::SummonPenguin()
	{
		mSpitTimeChecker += Time::DeltaTime();
	
		if (mSpitTimeChecker > mSpitTime)
		{
			mSpitTimeChecker = 0;
			if (!mbSpitting && mAnimator->GetPlayAnimation()->GetName() != L"AttackIntro")
			{
				mAnimator->Play(L"AttackIntro", false);
			}
		}
		
		if (mbSpitting)
		{
			mPenguinTimeChecker += Time::DeltaTime();
			if (mPenguinTimeChecker > mPenguinTime)
			{
				mPenguinTimeChecker = 0;
				++mPenguinCount;
				UINT randNum = rand() % mPenguinPosArr.size();
				UINT posNum = mPenguinPosArr[randNum];
				mPenguinPosArr.erase(mPenguinPosArr.begin() + randNum);
				Penguin* penguin = new Penguin(posNum);
				penguin->Initialize();
				SceneManager::GetCurScene()->AddGameObject(penguin, eColliderLayer::FrontMonster);
			}
			if (mPenguinCount > 4 && mPenguinTimeChecker > 1)
			{
				mAnimator->Play(L"AttackFin", false);
				mbSpitting = false;
				mPenguinCount = 0;
				mPenguinPosArr.clear();
				for (size_t i = 0; i < 6; i++)
				{
					mPenguinPosArr.push_back(i);
				}
			}
		}
	}

	void BeppiPhaseFour::SummonSwing()
	{
		if (mbFirstSummon)
		{
			for (size_t i = 0; i < 6; i++)
			{
				SwingPlatForm* swing = new SwingPlatForm();
				swing->Initialize();
				swing->SetPos({ -900 + 400.0f *i , 100 });
				SceneManager::GetCurScene()->AddGameObject(swing, eColliderLayer::FrontObject);
			}
			mbFirstSummon = false;
		}
		if (!mbIntro)
			mSwingFirstTimeChecker += Time::DeltaTime();

		if(!mbIntro && mSwingFirstTimeChecker > 2.5f)
			mSwingTimeChecker += Time::DeltaTime();

		if (mSwingTimeChecker > mSwingTime)
		{
			mSwingTimeChecker = 0;
			SwingPlatForm*  swing = new SwingPlatForm();
			swing->Initialize();
			SceneManager::GetCurScene()->AddGameObject(swing, eColliderLayer::FrontObject);
		}
	}

	void BeppiPhaseFour::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
	}

	void BeppiPhaseFour::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseFour::OnCollisonExit(Collider* other, Collider* my)
	{
	}


	void BeppiPhaseFour::AttackIntroCompleteEvent()
	{
		mAnimator->Play(L"AttackSpit", true);
		mbSpitting = true;
		mPenguinTimeChecker = 2;
	}

	void BeppiPhaseFour::AttackFinCompleteEvent()
	{
		mAnimator->Play(L"Idle", true);
	}

	void BeppiPhaseFour::Release()
	{
		mAnimator->Release();
		mLightAnimator->Release();
		mFrUmbrellaAnimator->Release();
		mBkUmbrellaAnimator->Release();
		Penguin(1).Release();
		SwingPlatForm().Release();
		RollerCoaster(0).Release();
	}

}