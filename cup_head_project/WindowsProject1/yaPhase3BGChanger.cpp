#include "yaPhase3BGChanger.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaBossCanRatScene.h"

namespace ya
{
	Phase3BGChanger::Phase3BGChanger()
	{
		SetName(L"Phase3BGChanger");
		SetPos({ 842,740 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Phase3BGChanger", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Wall\\Wall\\cat_wall_00", 6, 0.06f, false, false);

		mAnimator->GetCompleteEvent(L"Phase3BGChanger") = std::bind(&Phase3BGChanger::Phase3BGChangerCompleteEvent, this);
		mAnimator->Play(L"Phase3BGChanger", false);
	}

	Phase3BGChanger::~Phase3BGChanger()
	{
	}

	void Phase3BGChanger::Tick()
	{
		GameObject::Tick();
	}

	void Phase3BGChanger::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Phase3BGChanger::Phase3BGChangerCompleteEvent()
	{
		ObjectManager::Destroy(this);
		dynamic_cast<BossCanRatScene*>(SceneManager::GetCurScene())->ChangeLastBGQue();
	}

	void Phase3BGChanger::Release()
	{
		mAnimator->Release();
	}

}