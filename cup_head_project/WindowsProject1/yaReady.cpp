#include "yaReady.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaSound.h"
#include "yaResources.h"
namespace ya
{
	Ready::Ready()
	{
		SetName(L"BossReady");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });
		mSound1 = Resources::Load<Sound>(L"BossReadyAnnounce1", L"..\\Resources\\Sound\\Announcer\\sfx_level_announcer_0001_a.wav");
		mSound2 = Resources::Load<Sound>(L"BossReadyAnnounce2", L"..\\Resources\\Sound\\Announcer\\sfx_level_announcer_0002_a.wav");
		mSoundBell = Resources::Load<Sound>(L"BossReadyAnnounceBell", L"..\\Resources\\Sound\\Announcer\\sfx_level_knockout_bell.wav");

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Ready", L"..\\Resources\\Image\\Ready, WALLOP!\\FightText_GetReady_00", 52, 0.04f, false, false, { 0,0 }, false, true);

		mAnimator->GetCompleteEvent(L"Ready") = std::bind(&Ready::ReadyCompleteEvent, this);
		mAnimator->Play(L"Ready", false);
	}

	Ready::~Ready()
	{
	}

	void Ready::Tick()
	{
		GameObject::Tick();
		if (mTime == 0)
		{
			mSound1->Play(false);
		}
		mTime += Time::DeltaTime();
		if (mTime > 1.9f)
		{
			mTime = 0;
			mSound2->Play(false);
			mSoundBell->Play(false);
		}
		
	}

	void Ready::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ready::ReadyCompleteEvent()
	{
		ObjectManager::Destroy(this);
		SceneManager::GetCurScene()->SetIntro(false);
	}

}