#include "yaKnockOut.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
namespace ya
{
	KnockOut::KnockOut()
	{
		SetName(L"BossReady");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"KnockOut", L"..\\Resources\\Image\\A KNOCKOUT\\FightText_KO_00", 27, 0.05f, false, false, { 0,0 }, false, true);

		mAnimator->GetCompleteEvent(L"KnockOut") = std::bind(&KnockOut::KnockOutCompleteEvent, this);
		mAnimator->Play(L"KnockOut", false);
	}

	KnockOut::~KnockOut()
	{
	}

	void KnockOut::Tick()
	{
		Time::SlowDown(false);
		GameObject::Tick();		
		if (!isDead)
		{
			Time::SlowDown(true);
		}
	}

	void KnockOut::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void KnockOut::KnockOutCompleteEvent()
	{
		ObjectManager::Destroy(this);
		Time::SlowDown(false);
		isDead = true;
	}

}