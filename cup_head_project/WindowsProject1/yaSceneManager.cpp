#include "yaScenemanager.h"
#include "yaLogoScene.h"
#include "yaTitleScene.h"
#include "yaMapScene.h"
#include "yaBossBeppiScene.h"
#include "yaBossCarnationScene.h"
#include "yaBossCanRatScene.h"
#include "yaEndScene.h"
#include "yaObjectManager.h"
#include "yaSceneEnter.h"
#include "yaSceneExit.h"
#include "yaScoreScene.h"
namespace ya 
{
   
	Scene* SceneManager::mScenes[(UINT)eSceneType::Max] = {};
	Scene* SceneManager::mCurScene = nullptr;
	ScoreScene* SceneManager::mScoreScene = nullptr;
	void SceneManager::Initialize()
	{
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Map] = new MapScene();
		mScenes[(UINT)eSceneType::BossCarnation] = new BossCarnationScene();
		mScenes[(UINT)eSceneType::BossBeppi] = new BossBeppiScene();
		mScenes[(UINT)eSceneType::BossWernerWerman] = new BossCanRatScene();

		mScoreScene = new ScoreScene();
		mScenes[(UINT)eSceneType::Win] = mScoreScene;
		mScenes[(UINT)eSceneType::End] = new EndScene();

		for (size_t i = 0; i < 3; i++)
		{
			Scene* scene = mScenes[i];
			mCurScene = scene;
			scene->Initialize();
		}
		mCurScene = mScoreScene;
		mScoreScene->Initialize();
		
		mCurScene = mScenes[(UINT)eSceneType::Logo];
		mScenes[(UINT)eSceneType::Logo]->Enter();
	}

	void SceneManager::Tick()
	{
		mCurScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		mCurScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (size_t i = 0; i < (UINT)eSceneType::Max; i++)
		{
			if (mScenes[i] == nullptr)
				continue;
			delete mScenes[i];
			mScenes[i] = nullptr;
		}
	}

	ScoreScene* SceneManager::GetScoreScene()
	{
		return mScoreScene;
	}

	void SceneManager::DetroyGameObject()
	{
		ObjectManager::Release();
	}

	void SceneManager::ChangeScene(eSceneType type)
	{
		if (mCurScene == nullptr)
		{
			mCurScene = mScenes[(UINT)eSceneType::Logo];
		}
		else
		{
			SceneExit* sceneExit = new SceneExit(type);
			sceneExit->Initialize();
			mCurScene->AddGameObject(dynamic_cast<GameObject*>(sceneExit), eColliderLayer::Camera);
		}
	}
}