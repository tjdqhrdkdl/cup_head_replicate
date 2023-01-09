#include "yaBalloonDog.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaGround.h"
namespace ya
{
	BalloonDog::BalloonDog(Vector2 dir , bool pink)
		:mDir(dir)
		,mAliveTime(10.0f)
	{
		mPink = pink;
		SetName(L"BalloonDog");
		SetScale({ 120.0f, 100.0f });
		mHp = 4.0f;
		mCollider = new Collider();
		mCollider->SetAddPos({ 30,-30 });
		AddComponent(mCollider);
		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\Straight\\Dogs_Idle_", 8, 0.05f, true, false, { 30,0 })
			, mAnimator->CreateAnimation(L"LightenIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\Straight\\Lighten\\Dogs_Idle_", 8, 0.05f, true, false, { 30,0 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\Straight\\Dogs_Idle_", 8, 0.05f, true, true, { 0,0 })
			, mAnimator->CreateAnimation(L"LightenIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\Straight\\Lighten\\Dogs_Idle_", 8, 0.05f, true, true, { 0,0 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleRightUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalUp\\Dogs_Idle_", 8, 0.05f, true, false, { 0,50 })
			, mAnimator->CreateAnimation(L"LightenIdleRightUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalUp\\Lighten\\Dogs_Idle_", 8, 0.05f, true, false, {0,50}));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleLeftUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalUp\\Dogs_Idle_", 8, 0.05f, true, true, { 0,50 })
			, mAnimator->CreateAnimation(L"LightenIdleLeftUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalUp\\Lighten\\Dogs_Idle_", 8, 0.05f, true, true, { 0,50 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleRightDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalDown\\Dogs_Idle_", 8, 0.05f, true, false, { 50,50 })
			, mAnimator->CreateAnimation(L"LightenIdleRightDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalDown\\Lighten\\Dogs_Idle_", 8, 0.05f, true, false, { 50,50 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"IdleLeftDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalDown\\Dogs_Idle_", 8, 0.05f, true, true, { 20,60 })
			, mAnimator->CreateAnimation(L"LightenIdleLeftDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Idle\\DiagonalDown\\Lighten\\Dogs_Idle_", 8, 0.05f, true, true, { 20,60 }));

		mAnimator->CreateAnimation(L"ApearRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Apear\\Straight\\Dogs_Appear_", 13, 0.05f, true, false);
		mAnimator->CreateAnimation(L"ApearLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Apear\\Straight\\Dogs_Appear_", 13, 0.05f, true, true);
		mAnimator->CreateAnimation(L"ApearRightUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Apear\\DiagonalUp\\Dogs_Appear_", 13, 0.05f, true, false);
		mAnimator->CreateAnimation(L"ApearLeftUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Apear\\DiagonalUp\\Dogs_Appear_", 13, 0.05f, true, true);
		mAnimator->CreateAnimation(L"ApearRightDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Apear\\DiagonalDown\\Dogs_Appear_", 13, 0.05f, true, false);
		mAnimator->CreateAnimation(L"ApearLeftDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Apear\\DiagonalDown\\Dogs_Appear_", 13, 0.05f, true, true);


		mAnimator->CreateAnimation(L"Pop", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Dogs_Pop_", 7, 0.05f, true, false);


		mAnimator->GetCompleteEvent(L"ApearRight") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"ApearLeft") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"ApearRightUp") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"ApearLeftUp") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"ApearRightDown") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"ApearLeftDown") = std::bind(&BalloonDog::ApearCompleteEvent, this);


		mAnimator->GetCompleteEvent(L"Pop") = std::bind(&BalloonDog::PopCompleteEvent, this);
		
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"PinkIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Idle\\Straight\\pink_balloon_dog_chomp_00", 9, 0.05f, false, false, { 30,0 })
			, mAnimator->CreateAnimation(L"LightenPinkIdleRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Lighten\\Idle\\Straight\\pink_balloon_dog_chomp_00", 9, 0.05f, false, false, { 30,0 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"PinkIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Idle\\Straight\\pink_balloon_dog_chomp_00", 9, 0.05f, false, true, { 0,0 })
			, mAnimator->CreateAnimation(L"LightenPinkIdleLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Lighten\\Idle\\Straight\\pink_balloon_dog_chomp_00", 9, 0.05f, false, true, { 0,0 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"PinkIdleRightUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Idle\\DiagonalUp\\pink_balloon_dog_chomp_00", 9, 0.05f, false, false, { 0,50 })
			, mAnimator->CreateAnimation(L"LightenPinkIdleRightUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Lighten\\Idle\\DiagonalUp\\pink_balloon_dog_chomp_00", 9, 0.05f, false, false, { 0,50 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"PinkIdleLeftUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Idle\\DiagonalUp\\pink_balloon_dog_chomp_00", 9, 0.05f, false, true, { 0,50 })
			, mAnimator->CreateAnimation(L"LightenPinkIdleLeftUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Lighten\\Idle\\DiagonalUp\\pink_balloon_dog_chomp_00", 9, 0.05f, false, true, { 0,50 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"PinkIdleRightDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Idle\\DiagonalDown\\pink_balloon_dog_chomp_00", 9, 0.05f, false, false, { 50,50 })
			, mAnimator->CreateAnimation(L"LightenPinkIdleRightDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Lighten\\Idle\\DiagonalDown\\pink_balloon_dog_chomp_00", 9, 0.05f, false, false, { 50,50 }));
		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"PinkIdleLeftDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Idle\\DiagonalDown\\pink_balloon_dog_chomp_00", 9, 0.05f, false, true, { 20,60 })
			, mAnimator->CreateAnimation(L"LightenPinkIdleLeftDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Lighten\\Idle\\DiagonalDown\\pink_balloon_dog_chomp_00", 9, 0.05f, false, true, { 20,60 }));

		mAnimator->CreateAnimation(L"PinkApearRight", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Apear\\Straight\\pink_balloon_dog_intro_00", 14, 0.05f, false, false);
		mAnimator->CreateAnimation(L"PinkApearLeft", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Apear\\Straight\\pink_balloon_dog_intro_00", 14, 0.05f, false, true);
		mAnimator->CreateAnimation(L"PinkApearRightUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Apear\\DiagonalUp\\pink_balloon_dog_intro_00", 14, 0.05f, false, false);
		mAnimator->CreateAnimation(L"PinkApearLeftUp", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Apear\\DiagonalUp\\pink_balloon_dog_intro_00", 14, 0.05f, false, true);
		mAnimator->CreateAnimation(L"PinkApearRightDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Apear\\DiagonalDown\\pink_balloon_dog_intro_00", 14, 0.05f, false, false);
		mAnimator->CreateAnimation(L"PinkApearLeftDown", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Apear\\DiagonalDown\\pink_balloon_dog_intro_00", 14, 0.05f, false, true);


		mAnimator->CreateAnimation(L"PinkPop", L"..\\Resources\\Image\\Beppi\\Phase 2\\Balloon Dogs\\Pink\\Pop\\pink_balloon_dog_death_00", 8, 0.05f, false, false);


		mAnimator->GetCompleteEvent(L"PinkApearRight") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PinkApearLeft") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PinkApearRightUp") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PinkApearLeftUp") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PinkApearRightDown") = std::bind(&BalloonDog::ApearCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PinkApearLeftDown") = std::bind(&BalloonDog::ApearCompleteEvent, this);
									  
									  
		mAnimator->GetCompleteEvent(L"PinkPop") = std::bind(&BalloonDog::PopCompleteEvent, this);


		std::wstring dirStr = mDir.GetDirInStr();
		if (mPink)
			mAnimator->Play(L"PinkApear" + dirStr, false);
		else
			mAnimator->Play(L"Apear" + dirStr, false);

		mCollider->SetOff(true);

	}

	BalloonDog::~BalloonDog()
	{
	}

	void BalloonDog::Tick()
	{
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
			mAliveTimeChecker = 0;

		}
		if (mAnimator->GetPlayAnimation()->GetName() == L"Idle" + mDir.GetDirInStr()
			|| mAnimator->GetPlayAnimation()->GetName() == L"PinkIdle" + mDir.GetDirInStr()
			)
		{
			Vector2 pos = GetPos();
			pos -= mDestDir * 300.0f * Time::DeltaTime();
			SetPos(pos);
		}
		if (mHp < 0 )
		{
			if (mPink && mAnimator->GetPlayAnimation()->GetName() != L"PinkPop")
			{
				mAnimator->Play(L"PinkPop", false);
			}
			else if(!mPink && mAnimator->GetPlayAnimation()->GetName() != L"Pop")
			{
				mAnimator->Play(L"Pop", false);
			}
			mCollider->SetOff(true);
		}

		if (mParried && mAnimator->GetPlayAnimation()->GetName() != L"PinkPop")
		{
			mAnimator->Play(L"PinkPop", false);
			mCollider->SetOff(true);
		}
		Monster::Tick();
	}

	void BalloonDog::Render(HDC hdc)
	{

		Monster::Render(hdc);
	}

	void BalloonDog::OnCollisonEnter(Collider* other, Collider* my)
	{
		Monster::OnCollisonEnter(other,my);
		if(other->GetOwner()->GetLayer() == eColliderLayer::FrontObject
			&& dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			if (mPink)
				mAnimator->Play(L"PinkPop", false);
			else
				mAnimator->Play(L"Pop", false);
			mCollider->SetOff(true);
		}
	}

	void BalloonDog::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BalloonDog::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void BalloonDog::ApearCompleteEvent()
	{
		std::wstring dirStr = mDir.GetDirInStr();
		if(mPink)
			mAnimator->Play(L"PinkIdle" + dirStr, true);
		else
			mAnimator->Play(L"Idle"+dirStr, true);
		mCollider->SetOff(false);
		
	}

	void BalloonDog::PopCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

	void BalloonDog::Release()
	{
		mAnimator->Release();
	}


}