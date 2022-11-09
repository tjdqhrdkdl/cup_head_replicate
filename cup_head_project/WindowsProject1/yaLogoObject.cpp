#include "yaLogoObject.h"
#include "yaAnimator.h"
#include "yaCollider.h"
namespace ya
{
	LogoObject::LogoObject()
	{
		SetName(L"Logo");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Logo", L"..\\Resources\\Image\\Logo\\tile0", 100, 0.04f, true, false, {0,0}, false, false);
		mAnimator->Play(L"Logo", false);
	}

	LogoObject::~LogoObject()
	{
	}

	void LogoObject::Tick()
	{
		GameObject::Tick();
	}

	void LogoObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}