#include "yaSceneEnter.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaObjectManager.h"

namespace ya
{
	SceneEnter::SceneEnter(Scene* prev)
		:mPrevScene(prev)
	{
		
		SetName(L"SceneChangeEnter");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Enter", L"..\\Resources\\Image\\Camera\\Enter\\tile0", 17, 0.03f, true, false, { 0,0 }, false, true);

		mAnimator->GetCompleteEvent(L"Enter") = std::bind(&SceneEnter::AnimCompleteEvent, this);
		mAnimator->Play(L"Enter", false);
	}

	SceneEnter::~SceneEnter()
	{
	}

	void SceneEnter::Tick()
	{
		GameObject::Tick();
		SceneManager::GetCurScene()->SetStart(true);

	}

	void SceneEnter::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SceneEnter::AnimCompleteEvent()
	{
		ObjectManager::Destroy(this);
		SceneManager::GetCurScene()->ReleaseCameraObj();
	}

}