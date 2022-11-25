#include "yaOnHitEffect.h"

namespace ya
{
	OnHitEffect::OnHitEffect()
	{
		SetName(L"OnHitEffect");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Spark", L"..\\Resources\\Image\\Cuphead\\Hit\\Dust\\plane_hit_fx_00", 12, 0.04f, false, false, { 50,150 });

		mAnimator->Play(L"Spark", false);
		mAnimator->GetCompleteEvent(L"Spark") = std::bind(&OnHitEffect::EffectCompleteEvent, this);
	}

	OnHitEffect::~OnHitEffect()
	{

	}

	void OnHitEffect::Tick()
	{
		GameObject::Tick();
	}

	void OnHitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void OnHitEffect::EffectCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}
}