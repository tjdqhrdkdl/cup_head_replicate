#include "yaPhase3BGExplodeEffect.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"

namespace ya
{
	Phase3BGExplodeEffect::Phase3BGExplodeEffect()
	{
		SetName(L"Phase3BGExplodeEffect");
		SetPos({ 800,700 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Phase3BGExplodeEffect", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wall\\Explode\\cat_wall_explode_00", 17, 0.07f, false, false);

		mAnimator->GetCompleteEvent(L"Phase3BGExplodeEffect") = std::bind(&Phase3BGExplodeEffect::Phase3BGExplodeEffectCompleteEvent, this);
		mAnimator->Play(L"Phase3BGExplodeEffect", false);
	}

	Phase3BGExplodeEffect::~Phase3BGExplodeEffect()
	{
	}

	void Phase3BGExplodeEffect::Tick()
	{
		GameObject::Tick();
	}

	void Phase3BGExplodeEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Phase3BGExplodeEffect::Phase3BGExplodeEffectCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

	void Phase3BGExplodeEffect::Release()
	{
		mAnimator->Release();
	}

}