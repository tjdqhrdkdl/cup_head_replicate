#include "yaBeppiPh2Body.h"
#include "yaAnimator.h"
#include "yaTime.h"
namespace ya
{
	BeppiPh2Body::BeppiPh2Body()
		:mIntroMove(true)
		,mVelocity({0,0})
	{
		
		SetPos({ 800,1300 });
		mBodyAnimator = new Animator();
		mTankAnimator = new Animator();
		mLeftBottleAnimator = new Animator();
		mRightBottleAnimator = new Animator();
		mLeftPipeAnimator = new Animator();
		mRightPipeAnimator = new Animator();

		AddComponent(mLeftPipeAnimator);
		AddComponent(mRightPipeAnimator);
		AddComponent(mLeftBottleAnimator);
		AddComponent(mRightBottleAnimator);
		AddComponent(mTankAnimator);
		AddComponent(mBodyAnimator);

		mBodyAnimator->CreateAnimation(L"BodyIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Body\\1_Phase2_Body_", 16, 0.05f, true, false, {0,-30});
		mTankAnimator->CreateAnimation(L"TankIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Helium Tank\\1_HeliumTank_", 4, 0.1f, false, false,{0,350});
		mLeftPipeAnimator->CreateAnimation(L"LeftPipeIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Helium Pipes\\HeliumPipes_Idle_", 3, 0.1f, true, true, { -568,-63 });
		mRightPipeAnimator->CreateAnimation(L"RightPipeIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Helium Pipes\\HeliumPipes_Idle_", 3, 0.1f, true, false, { 560,-57 });
		mRightBottleAnimator->CreateAnimation(L"RightBottleIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Helium Bottles\\RightHeliumBottle_", 14, 0.05f, true, false,{235,40});
		mLeftBottleAnimator->CreateAnimation(L"LeftBottleIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Idle\\Helium Bottles\\LeftHeliumBottle_", 14, 0.05f, true, false, { -230,40 });
		mLeftPipeAnimator->CreateAnimation(L"LeftPipeIntro", L"..\\Resources\\Image\\Beppi\\Phase 2\\Intro\\Helium Pipes\\HeliumPipes_Intro_", 24, 0.05f, true, true, { -568,-63 });
		mRightPipeAnimator->CreateAnimation(L"RightPipeIntro", L"..\\Resources\\Image\\Beppi\\Phase 2\\Intro\\Helium Pipes\\HeliumPipes_Intro_", 24, 0.05f, true, false, { 560,-57 });

		mLeftPipeAnimator->GetCompleteEvent(L"LeftPipeIntro") = std::bind(&BeppiPh2Body::PipeIntroCompleteEvent, this);

		mTankAnimator->Play(L"TankIdle", true);
		mLeftBottleAnimator->Play(L"LeftBottleIdle", true);
		mRightBottleAnimator->Play(L"RightBottleIdle", true);
		mTankAnimator->SetStop(true);
		mLeftBottleAnimator->SetStop(true);
		mRightBottleAnimator->SetStop(true);

		mLeftPipeAnimator->DeleteGDIPlusImage();
		mRightPipeAnimator->DeleteGDIPlusImage();
		mLeftBottleAnimator->DeleteGDIPlusImage();
		mRightBottleAnimator->DeleteGDIPlusImage();
		mTankAnimator->DeleteGDIPlusImage();
		mBodyAnimator->DeleteGDIPlusImage();

		
	}
	BeppiPh2Body::~BeppiPh2Body()
	{
	}

	void BeppiPh2Body::Tick()
	{
		if (mIntroMove)
		{
			Vector2 pos = GetPos();
			pos.y -= 200 * Time::DeltaTime();
			if (pos.y < 600)
			{
				pos.y = 600;
				mIntroMove = false;
			}
			SetPos(pos);
		}
		if (IsDeathTimeOn())
		{
			Vector2 pos = GetPos();
			pos.y += mVelocity.y * Time::DeltaTime();
			mVelocity.y += 800 * Time::DeltaTime();
			SetPos(pos);
		}
		GameObject::Tick();
	}

	void BeppiPh2Body::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BeppiPh2Body::IntroCue1()
	{
		mTankAnimator->SetStop(false);
		mLeftBottleAnimator->SetStop(false);
		mRightBottleAnimator->SetStop(false);
		mLeftPipeAnimator->Play(L"LeftPipeIntro", false);
		mRightPipeAnimator->Play(L"RightPipeIntro", false);
	}

	void BeppiPh2Body::IntroCue2()
	{
		mBodyAnimator->Play(L"BodyIdle", true);
	}

	void BeppiPh2Body::PipeIntroCompleteEvent()
	{
		mLeftPipeAnimator->Play(L"LeftPipeIdle", true);
		mRightPipeAnimator->Play(L"RightPipeIdle", true);
	}

}