#include "yaReadyAnimation.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	ReadyAnimation::ReadyAnimation()
	{
		SetName(L"Logo");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Ready", L"..\\Resources\\Image\\Title Screen\\Cuphead and Mugman\\cuphead_title_screen_00", 35, 0.03f, false, false, { 0,0 }, false, false);
		mAnimator->Play(L"Ready", true);

		mAnimator->DeleteGDIPlusImage();
	}

	ReadyAnimation::~ReadyAnimation()
	{
	}

	void ReadyAnimation::Tick()
	{
		GameObject::Tick();
	}

	void ReadyAnimation::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}