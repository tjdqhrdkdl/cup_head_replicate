#include "yaLogoAnimation.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaLogoScene.h"	
#include "yaResources.h"
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


		mAnimator->DeleteGDIPlusImage();
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
		}
	}

	void LogoAnimation::Render(HDC hdc)
	{
		if(mTime < 1.0f)
			GameObject::Render(hdc);
	}

	void LogoAnimation::LogoCompleteEvent()
	{
		mComplete = true;
		dynamic_cast<LogoScene*>(SceneManager::GetCurScene())->SetReady();

	}

}