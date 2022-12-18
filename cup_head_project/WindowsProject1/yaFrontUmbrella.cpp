#include "yaFrontUmbrella.h"
#include "yaAnimator.h"
namespace ya
{
	FrontUmbrella::FrontUmbrella()
	{
		SetName(L"BeppiPhaseFour");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"FrUmbrellaIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Umbrella\\Front\\Idle\\umbrella_fr_spin_00", 19, 0.06f, false, false, { 0,-840 });
		mAnimator->CreateAnimation(L"FrUmbrellaIntro", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Phase 4\\Umbrella\\Front\\Intro\\umbrella_fr_open_00", 10, 0.05f, false, false, { 0,-700 });

		mAnimator->GetCompleteEvent(L"FrUmbrellaIntro") = std::bind(&FrontUmbrella::IntroCompleteEvent, this);
	}

	FrontUmbrella::~FrontUmbrella()
	{
	}

	void FrontUmbrella::Tick()
	{
		GameObject::Tick();
	}

	void FrontUmbrella::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FrontUmbrella::IntroCompleteEvent()
	{
		mIntroFin = true;
		mAnimator->Play(L"FrUmbrellaIdle", true);
	}

	void FrontUmbrella::Release()
	{
		mAnimator->Release();
	}

}