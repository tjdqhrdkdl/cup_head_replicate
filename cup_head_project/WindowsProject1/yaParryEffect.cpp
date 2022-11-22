#include "yaParryEffect.h"

namespace ya 
{
	ParryEffect::ParryEffect()
	{
		SetName(L"ParryEffect");
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Spark", L"..\\Resources\\Image\\Cuphead\\Parry\\Hand\\Effect\\cuphead_slap_spark_00", 10, 0.08f, false, false, {0,50});

		mAnimator->Play(L"Spark", false);
		mAnimator->GetCompleteEvent(L"Spark") = std::bind(&ParryEffect::EffectCompleteEvent, this);
	}

	ParryEffect::~ParryEffect()
	{

	}

	void ParryEffect::Tick()
	{
		GameObject::Tick();
	}

	void ParryEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ParryEffect::EffectCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}
}