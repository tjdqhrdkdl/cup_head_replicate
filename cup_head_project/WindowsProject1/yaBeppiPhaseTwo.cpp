#include "yaBeppiPhaseTwo.h"
#include "yaTime.h"
#include "yaBullet.h"
#include "yaScenemanager.h"
#include "yaScene.h"
#include "yaInput.h"
#include "yaPicture.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaBalloonDog.h"
#include "yaRollerCoaster.h"
#include "yaBossBeppiScene.h"
#include "yaPlayer.h"
#include "yaBossExplosion.h"
namespace ya
{
	BeppiPhaseTwo::BeppiPhaseTwo()
		: mBalloonTime(2.0f)
		, mBalloonTimeChecker(0)
		, mCoasterTime(15.0f)
		, mCoasterTimeChecker(10)
		, misIntroApear(true)
	{
		SetName(L"BeppiPhaseTwo");
		mHp = 200;
		SetPos({ 800,1500 });
		SetScale({ 400.0f,400.0f });
		mCollider = new Collider();
		mCollider->SetDanger(false);
		AddComponent(mCollider);
		mAnimator = new Animator();
		AddComponent(mAnimator);
		

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"HeadIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Head\\Phase2_Idle_Head_", 24, 0.05f, true, false ,{0,300})
			, mAnimator->CreateAnimation(L"LightenHeadIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Head\\Lighten\\Phase2_Idle_Head_", 24, 0.05f, true, false, { 0,300 }));

		mAnimator->CreateAnimation(L"IntroApear", L"..\\Resources\\Image\\Beppi\\Phase 2\\Intro\\Beppi\\IntroApear\\Phase2_Intro_", 5, 0.1f, true, false, { -7,-30 });
		mAnimator->CreateAnimation(L"IntroBulkup", L"..\\Resources\\Image\\Beppi\\Phase 2\\Intro\\Beppi\\IntroBulkup\\Phase2_Intro_", 19, 0.05f, true, false, { 0,-45 });
		
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IntroBalloon", L"..\\Resources\\Image\\Beppi\\Phase 2\\Intro\\Beppi\\IntroBalloon\\Phase2_Intro_", 4, 0.1f, true, false, { 0,-100 })
			, mAnimator->CreateAnimation(L"LightenIntroBalloon", L"..\\Resources\\Image\\Beppi\\Phase 2\\Intro\\Beppi\\IntroBalloon\\Lighten\\Phase2_Intro_", 4, 0.1f, true, false, { 0,-100 }));

		mAnimator->CreateAnimation(L"End", L"..\\Resources\\Image\\Beppi\\Phase 2\\End\\Phase2_End_", 7, 0.1f, true, false, { 0,300 });


		mAnimator->GetCompleteEvent(L"IntroBulkup") = std::bind(&BeppiPhaseTwo::IntroBulkupCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"IntroBalloon") = std::bind(&BeppiPhaseTwo::IntroBalloonCompleteEvent, this);


		mAnimator->Play(L"IntroApear", true);
		
		mCollider->SetOff(true);
		

		BalloonDog({1,0});
		RollerCoaster(10);

		BeppiPh2Body();
		BossExplosion();

		mAnimator->DeleteGDIPlusImage();
	}

	BeppiPhaseTwo::~BeppiPhaseTwo()
	{
	}

	void BeppiPhaseTwo::Tick()
	{
		Monster::Tick();

		Move();
		if (mAnimator->GetPlayAnimation()->GetName() == L"HeadIdle")
		{
			SummonBalloonDogs();
			SummonCoaster();
		}
		if (IsDeathTimeOn())
		{
			mDeathEffectTimeChecker += Time::DeltaTime();
			if (mDeathEffectTimeChecker > 0.4f + (rand() % 5) * 0.1)
			{
				mDeathEffectTimeChecker = 0;
				Vector2 pos = GetPos();
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

				effect->SetPos(pos);
			}
		}

	}

	void BeppiPhaseTwo::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}


	void BeppiPhaseTwo::Move()
	{
		Vector2 pos = GetPos();
		if (mAnimator->GetPlayAnimation()->GetName() == L"HeadIdle")
		{
			if (pos.x > 820)
				mbMoveLeft = true;
			else if (pos.x < 780)
				mbMoveLeft = false;

			if (pos.y > 310)
				mbMoveDown = false;
			else if (pos.y < 290)
				mbMoveDown = true;

			if (mbMoveDown)
				pos.y += 5 * Time::DeltaTime();
			else
				pos.y -= 5 * Time::DeltaTime();

			if (mbMoveLeft)
				pos.x -= 10 * Time::DeltaTime();
			else
				pos.x += 10 * Time::DeltaTime();
		}

		else if (mAnimator->GetPlayAnimation()->GetName() == L"IntroApear")
		{
			pos.y -= 200 * Time::DeltaTime();
			if (pos.y < 780)
			{
				pos.y = 780;
				mAnimator->Play(L"IntroBulkup", false);
				mPh2Body->IntroCue1();
			}
		}
		else if (mAnimator->GetPlayAnimation()->GetName() == L"IntroBalloon")
		{
			pos.y -= 100 * Time::DeltaTime();
			if (pos.y < 300)
			{
				pos.y = 300;
				mAnimator->Play(L"HeadIdle", true);
			}
		}
		else if (IsDeathTimeOn() && GetDeathTime() > 3)
		{
			pos.y += 40 * Time::DeltaTime();
		}
		else if (IsDeathTimeOn() && GetDeathTime() < 3)
		{
			pos.y -= 500 * Time::DeltaTime();
		}
		SetPos(pos);
	}

	void BeppiPhaseTwo::SummonBalloonDogs()
	{
		mBalloonTimeChecker += Time::DeltaTime();
		if (mBalloonTimeChecker > mBalloonTime)
		{
			bool pink = false;
			mBalloonTimeChecker = 0;
			mBalloonPoint += 1;
			mPinkBalloonCount += 1;
			if (mBalloonPoint > 5)
				mBalloonPoint = 0;
			if (mPinkBalloonCount > 3)
			{
				pink = true;
				mPinkBalloonCount = 0;
			}
			Player* player = dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->GetScenePlayer();
			Vector2 playerPos = player->GetPos();
			Vector2 BalloonPos = {};
			Vector2 BalloonDir;

			switch (mBalloonPoint)
			{
			case 0:
				BalloonPos = { 90,500 };
				break;
			case 1:
				BalloonPos = { 110,223 };
				break;
			case 2:
				BalloonPos = { 375,203 };
				break;
			case 3:
				BalloonPos = { 1510,515 };
				break;
			case 4:
				BalloonPos = { 1480,210 };
				break;
			case 5:
				BalloonPos = { 1210,215 };
				break;
			}
			if (playerPos.x < BalloonPos.x)
			{
				if (playerPos.y > BalloonPos.y + 200)
					BalloonDir = Vector2::LeftDown;
				else if (playerPos.y < BalloonPos.y - 100)
					BalloonDir = Vector2::LeftUp;
				else
					BalloonDir = Vector2::Left;
			}
			else
			{
				if (playerPos.y > BalloonPos.y + 200)
					BalloonDir = Vector2::RightDown;
				else if (playerPos.y < BalloonPos.y - 100)
					BalloonDir = Vector2::RightUp;
				else
					BalloonDir = Vector2::Right;
			}

			Vector2 destDir = BalloonPos - playerPos;
			BalloonDog* dog = new BalloonDog(BalloonDir , pink);
			dog->SetPos(BalloonPos);
			dog->SetDestDir(destDir.Normalize());
			dog->Initialize();
			SceneManager::GetCurScene()->AddGameObject(dog,eColliderLayer::FrontMonster);
		}
	}

	void BeppiPhaseTwo::SummonCoaster()
	{
		mCoasterTimeChecker += Time::DeltaTime();
		if (mCoasterTimeChecker > mCoasterTime)
		{
			mCoasterTimeChecker = 0;
			RollerCoaster* coaster = new RollerCoaster(10);
			coaster->Initialize();
			SceneManager::GetCurScene()->AddGameObject(coaster, eColliderLayer::FrontObject);
		}
	}

	void BeppiPhaseTwo::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other, my);
		if (mDead && !IsDeathTimeOn())
		{
			mAnimator->Play(L"End", true);

			ObjectManager::Destroy(this, 5.0f);
			ObjectManager::Destroy(mPh2Body, 3);
			dynamic_cast<BossBeppiScene*>(SceneManager::GetCurScene())->SetPhase(3);
		}
	}

	void BeppiPhaseTwo::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BeppiPhaseTwo::OnCollisonExit(Collider* other, Collider* my)
	{
	}


	void BeppiPhaseTwo::IntroBulkupCompleteEvent()
	{
		mAnimator->Play(L"IntroBalloon", false);
		SceneManager::GetCurScene()->ChangeLayer(this, eColliderLayer::FrontMonster);
		mCollider->SetOff(false);
		mCollider->SetAddPos({ 0,-400 });
		mPh2Body->IntroCue2();
	}

	void BeppiPhaseTwo::IntroBalloonCompleteEvent()
	{
		mAnimator->Play(L"HeadIdle", true);
		SetPos({ 820, 300 });
		mCollider->SetAddPos({ 0,0 });
	}

}