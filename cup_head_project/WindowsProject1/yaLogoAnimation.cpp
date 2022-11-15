#include "yaLogoAnimation.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
namespace ya
{
	LogoAnimation::LogoAnimation()
		:mComplete(false)
	{
		SetName(L"Logo");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Logo", L"..\\Resources\\Image\\Logo\\tile0", 100, 0.03f, true, false, {0,0}, false, false);

		mAnimator->GetCompleteEvent(L"Logo") = std::bind( & LogoAnimation::LogoCompleteEvent, this);
		mAnimator->Play(L"Logo", false);
	}

	LogoAnimation::~LogoAnimation()
	{
	}

	void LogoAnimation::Tick()
	{
		GameObject::Tick();
		if (mComplete == true)
		{
			mTime += Time::DeltaTime();
			mAnimator->SetMatrixToTransparent((mTime));
			if (mTime >= 1.0f)
				ObjectManager::Destroy(this);
		}
	}

	void LogoAnimation::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void LogoAnimation::LogoCompleteEvent()
	{
		mComplete = true;
	}

}