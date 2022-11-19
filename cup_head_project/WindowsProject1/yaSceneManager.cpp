#include "yaScenemanager.h"
#include "yaLogoScene.h"
#include "yaTitleScene.h"
#include "yaMapScene.h"
#include "yaBossBeppiScene.h"
#include "yaBossVegetableScene.h"
#include "yaEndScene.h"
#include "yaObjectManager.h"
namespace ya {
   
	Scene* SceneManager::mScenes[(UINT)eSceneType::Max] = {};
	Scene* SceneManager::mCurScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Map] = new MapScene();
		mScenes[(UINT)eSceneType::BossVegetable] = new BossVegetableScene();
		mScenes[(UINT)eSceneType::BossBeppi] = new BossBeppiScene();
		mScenes[(UINT)eSceneType::End] = new EndScene();

		for (Scene* scene : mScenes )
		{
			mCurScene = scene;
			scene->Initialize();
		}

		ChangeScene(eSceneType::Logo);
		
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

	void SceneManager::DetroyGameObject()
	{
		ya::ObjectManager::Release();
	}

	void SceneManager::ChangeScene(eSceneType type)
	{
		if (mCurScene == nullptr)
		{
			mCurScene = mScenes[(UINT)eSceneType::Logo];
		}
		else
		{
			mCurScene->Exit();
			mCurScene = mScenes[(UINT)type];
		}

		mCurScene->Enter();
	}
}