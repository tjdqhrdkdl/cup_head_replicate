#include "yaVenus.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaObjectManager.h"
#include "yaBossCarnationScene.h"
#include "yaPlayer.h"
#include "yaGround.h"
namespace ya
{
	Venus::Venus()
		:mbIsSeed(true)
	{
		SetName(L"Venus");
		mHp = 8;
		SetScale({ 50.0f,50.0f });
		mCollider = new Collider();
		AddComponent(mCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mVineAnimator = new Animator();
		AddComponent(mVineAnimator);
		mVineAnimator->CreateAnimation(L"GroundBurst", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\flower_vine_groundburst_00", 8, 0.04f, false, false);
		mVineAnimator->CreateAnimation(L"VineA", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\VFT_Vine_", 17, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"VineB", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\MF_Vine_B_", 18, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"VineC", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Vine_C_", 21, 0.04f, false, false);
		mVineAnimator->CreateAnimation(L"ReverseVineA", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Reversed\\VFT_Vine_", 17, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"ReverseVineB", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Reversed\\MF_Vine_B_", 18, 0.04f, true, false);
		mVineAnimator->CreateAnimation(L"ReverseVineC", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Vine\\Reversed\\Vine_C_", 21, 0.04f, false, false);


		mAnimator->CreateAnimation(L"SeedFall", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Venus\\Seed\\Seed_Fall_A_", 36, 0.04f, false, false);
		mAnimator->CreateAnimation(L"SeedArrive", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Venus\\Seed\\Seed_Grow_", 8, 0.04f, false, false);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IntroLeft", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Venus\\Intro\\Venus_", 6, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenIntroLeft", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Seeds\\Venus\\Intro\\Venus_", 6, 0.04f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IntroRight", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Venus\\Intro\\Venus_", 6, 0.04f, false, true)
			, mAnimator->CreateAnimation(L"LightenIntroRight", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Seeds\\Venus\\Intro\\Venus_", 6, 0.04f, false, true));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Venus\\Idle\\Venus_", 6, 0.04f, false, false)
			, mAnimator->CreateAnimation(L"LightenIdleLeft", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Seeds\\Venus\\Idle\\Venus_", 6, 0.04f, false, false));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Venus\\Idle\\Venus_", 6, 0.04f, false, true)
			, mAnimator->CreateAnimation(L"LightenIdleRight", L"..\\Resources\\Image\\Cagney Carnation\\Lighten\\Firing Seeds\\Seeds\\Venus\\Idle\\Venus_", 6, 0.04f, false, true));

		mAnimator->CreateAnimation(L"Death", L"..\\Resources\\Image\\Cagney Carnation\\Firing Seeds\\Seeds\\Venus\\Death\\Venus_Die_", 11, 0.04f, false, false);

		mAnimator->GetCompleteEvent(L"SeedArrive") = std::bind(&Venus::ArriveCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Death") = std::bind(&Venus::DeathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"IntroRight") = std::bind(&Venus::IntroCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"IntroLeft") = std::bind(&Venus::IntroCompleteEvent, this);

		mVineAnimator->GetCompleteEvent(L"GroundBurst") = std::bind(&Venus::GroundBurstCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"VineA") = std::bind(&Venus::VineGrowCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"VineB") = std::bind(&Venus::VineGrowCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"VineC") = std::bind(&Venus::VineGrowCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"ReverseVineA") = std::bind(&Venus::VineReverseCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"ReverseVineB") = std::bind(&Venus::VineReverseCompleteEvent, this);
		mVineAnimator->GetCompleteEvent(L"ReverseVineC") = std::bind(&Venus::VineReverseCompleteEvent, this);

		mAnimator->Play(L"SeedFall", true);
	}

	Venus::~Venus()
	{
	}

	void Venus::Tick()
	{
		Monster::Tick();
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > 25)
		{
			mAnimator->Play(L"Death", false);
			mCollider->SetOff(true);
		}
		Vector2 pos = GetPos();
		if (mAnimator->GetPlayAnimation() != nullptr)
		{
			if (mAnimator->GetPlayAnimation()->GetName() == L"SeedFall")
			{
				pos.y += 300 * Time::DeltaTime();
			}

			if (mAnimator->GetPlayAnimation()->GetName() == L"IdleRight" 
				|| mAnimator->GetPlayAnimation()->GetName() == L"IdleLeft"
				)
			{
				pos.x += Time::DeltaTime() * 100 * mDestDir.x;
				pos.y += Time::DeltaTime() * 100 * mDestDir.y;

				mVineAnimator->SetAddPos({ mVineAnimator->GetAddPos().x - Time::DeltaTime() * 100 * mDestDir.x, mVineAnimator->GetAddPos().y - Time::DeltaTime() * 100 * mDestDir.y});

			}
			SetPos(pos);

			if (mHp < 0 && mAnimator->GetPlayAnimation()->GetName() != L"Death")
			{
				mAnimator->Play(L"Death", false);
				mCollider->SetOff(true);
			}
		}
	}

	void Venus::Render(HDC hdc)
	{
		Monster::Render(hdc);
	}

	void Venus::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			if(mAnimator->GetPlayAnimation()->GetName() == L"SeedFall")
				mAnimator->Play(L"SeedArrive", false);

			else if (mAnimator->GetPlayAnimation()->GetName() == L"IdleRight"
				|| mAnimator->GetPlayAnimation()->GetName() == L"IdleLeft"
				)
			{
				mAnimator->Play(L"Death", false);
			}
		}
	}

	void Venus::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Venus::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Venus::ArriveCompleteEvent()
	{
		mAnimator->SetPlayAnimation(nullptr);
		mVineAnimator->Play(L"GroundBurst", false);
	}

	void Venus::GroundBurstCompleteEvent()
	{
		switch (rand() % 3)
		{
		case 0:
			mVineAnimator->Play(L"VineA", false);
			break;
		case 1:
			mVineAnimator->Play(L"VineB", false);
			break;
		case 2:
			mVineAnimator->Play(L"VineC", false);
			break;
		}
		SceneManager::GetCurScene()->ChangeLayer(this, eColliderLayer::FrontMonster);
		mCollider->SetScale({ 70,70 });
	}

	void Venus::VineGrowCompleteEvent()
	{
		Vector2 pos = GetPos();
		if (mVineAnimator->GetPlayAnimation()->GetName() == L"VineA")
		{
			pos.y -= 310;
			mVineAnimator->Play(L"ReverseVineA", false);
			mVineAnimator->SetAddPos({ 0,310 });
		}
		else if (mVineAnimator->GetPlayAnimation()->GetName() == L"VineB")
		{
			pos.y -= 390;
			mVineAnimator->Play(L"ReverseVineB", false);
			mVineAnimator->SetAddPos({ 0,390 });

		}
		else if (mVineAnimator->GetPlayAnimation()->GetName() == L"VineC")
		{
			pos.y -= 470;
			mVineAnimator->SetAddPos({ 0,470 });
			mVineAnimator->Play(L"ReverseVineC", false);
		}
		SetPos(pos);
		Vector2 plPos = dynamic_cast<BossCarnationScene*>(SceneManager::GetCurScene())->GetScenePlayer()->GetPos();
		mDestDir = (plPos - GetPos()).Normalize();
		if (mDestDir.x <= 0)
			mAnimator->Play(L"IntroLeft", false);
		else
			mAnimator->Play(L"IntroRight", false);
	}

	void Venus::VineReverseCompleteEvent()
	{
		mVineAnimator->SetPlayAnimation(nullptr);
	}

	void Venus::IntroCompleteEvent()
	{
		if (mDestDir.x <= 0)
			mAnimator->Play(L"IdleLeft", true);
		else
			mAnimator->Play(L"IdleRight", true);
	}

	void Venus::DeathCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}
	void Venus::Release()
	{
	}

}