#include "yaDashEffect.h"


namespace ya
{
	DashEffect::DashEffect(bool left)
	{
		SetName(L"Dash");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		isLeft = left;
		mAnimator->CreateAnimation(L"DustRight", L"..\\Resources\\Image\\Cuphead\\Dash\\Effect\\Sprite\\player_dashDustA_00", 16, 0.04f, false, false, { 0,0 });
		mAnimator->CreateAnimation(L"DustLeft", L"..\\Resources\\Image\\Cuphead\\Dash\\Effect\\Sprite\\player_dashDustA_00", 16, 0.04f, false, true, { 0,0 });

		if (isLeft)
			mAnimator->Play(L"DustLeft", false);
		else
			mAnimator->Play(L"DustRight", false);

		mAnimator->GetCompleteEvent(L"DustLeft") = std::bind(&DashEffect::EffectCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DustRight") = std::bind(&DashEffect::EffectCompleteEvent, this);
	}

	DashEffect::~DashEffect()
	{
	}

	void DashEffect::Tick()
	{
		GameObject::Tick();
	}

	void DashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DashEffect::EffectCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

}