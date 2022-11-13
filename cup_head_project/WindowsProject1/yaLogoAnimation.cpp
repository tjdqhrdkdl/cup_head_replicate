#include "yaLogoAnimation.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
namespace ya
{
	LogoAnimation::LogoAnimation()
	{
		SetName(L"Logo");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Logo", L"..\\Resources\\Image\\Logo\\tile0", 100, 0.03f, true, false, {0,0}, false, false);
		mAnimator->Play(L"Logo", false);
	}

	LogoAnimation::~LogoAnimation()
	{
	}

	void LogoAnimation::Tick()
	{
		
		GameObject::Tick();
		mTime += Time::DeltaTime();
		if (mTime > 9.0f)
		{
			mAnimator->SetMatrixToTransparent((mTime - 9));
		}
		if (mTime > 10.0f)
			ObjectManager::Destroy(this);
	}

	void LogoAnimation::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}