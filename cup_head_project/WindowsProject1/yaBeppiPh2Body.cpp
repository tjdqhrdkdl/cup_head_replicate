#include "yaBeppiPh2Body.h"
#include "yaAnimator.h"

namespace ya
{
	BeppiPh2Body::BeppiPh2Body()
	{
		SetPos({ 800,600 });
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
		
		mBodyAnimator->Play(L"BodyIdle", true);
		mTankAnimator->Play(L"TankIdle", true);
		mLeftBottleAnimator->Play(L"LeftBottleIdle", true);
		mRightBottleAnimator->Play(L"RightBottleIdle", true);
		mLeftPipeAnimator->Play(L"LeftPipeIdle", true);
		mRightPipeAnimator->Play(L"RightPipeIdle", true);

	}
	BeppiPh2Body::~BeppiPh2Body()
	{
	}

	void BeppiPh2Body::Tick()
	{
		GameObject::Tick();
	}

	void BeppiPh2Body::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}