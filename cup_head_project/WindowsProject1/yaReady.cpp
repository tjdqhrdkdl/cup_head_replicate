#include "yaReady.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
namespace ya
{
	Ready::Ready()
		:mComplete(false)
	{
		SetName(L"BossReady");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Ready", L"..\\Resources\\Image\\Ready, WALLOP!\\FightText_GetReady_00", 52, 0.03f, false, false, { 0,0 }, false, true);

		mAnimator->GetCompleteEvent(L"Ready") = std::bind(&Ready::ReadyCompleteEvent, this);
		mAnimator->Play(L"Ready", false);
	}

	Ready::~Ready()
	{
	}

	void Ready::Tick()
	{
		GameObject::Tick();
		if (mComplete == true)
		{
			ObjectManager::Destroy(this);
		}
	}

	void Ready::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ready::ReadyCompleteEvent()
	{
		mComplete = true;
		SceneManager::GetCurScene()->SetIntro(false);
	}

}