#include "yaBossExplosion.h"
#include "yaAnimator.h"
namespace ya
{
	BossExplosion::BossExplosion()
	{

		SetName(L"BossExplosion");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Boom", L"..\\Resources\\Image\\BossExplosion\\boss_explosion_00", 12, 0.04f, false, false, { 0,0 });

		mAnimator->Play(L"Boom", true);

		mAnimator->GetCompleteEvent(L"Boom") = std::bind(&BossExplosion::EffectCompleteEvent, this);
	}

	BossExplosion::~BossExplosion()
	{
	}

	void BossExplosion::Tick()
	{
		GameObject::Tick();
	}

	void BossExplosion::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossExplosion::EffectCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

}