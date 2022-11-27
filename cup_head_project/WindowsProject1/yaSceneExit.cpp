#include "yaSceneExit.h"
#include "yaAnimator.h"
#include "yaObjectManager.h"
#include "yaSceneEnter.h"
namespace ya
{
	SceneExit::SceneExit(eSceneType type)
	{
		SetName(L"SceneChangeExit");
		SetPos({ 800,900 });
		SetScale({ 1600,900 });
		mType = type;
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Exit", L"..\\Resources\\Image\\Camera\\Exit\\tile00", 17, 0.03f, true, false, { 0,0 }, true, true);

		mAnimator->GetCompleteEvent(L"Exit") = std::bind(&SceneExit::AnimCompleteEvent, this);
		mAnimator->Play(L"Exit", true);
	}

	SceneExit::~SceneExit()
	{
	}

	void SceneExit::Tick()
	{
		GameObject::Tick();
	}

	void SceneExit::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SceneExit::AnimCompleteEvent()
	{
		ObjectManager::Destroy(this);
		Scene* prevScene = SceneManager::GetCurScene();
		prevScene->Exit();

		SceneManager::SetCurScene(mType);
		SceneManager::GetCurScene()->Enter();

		SceneEnter* sceneEnter = new SceneEnter(prevScene);
		sceneEnter->Initialize();
		SceneManager::GetCurScene()->AddGameObject(dynamic_cast<GameObject*>(sceneEnter), eColliderLayer::Camera);
	}

}