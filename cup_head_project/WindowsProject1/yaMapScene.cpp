#include "yaMapScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaUIManager.h"
namespace ya {
	MapScene::MapScene()
	{
	}

	MapScene::~MapScene()
	{
	}

	void MapScene::Initialize()
	{

		AddGameObject(new Player(), eColliderLayer::Player);
		Scene::Initialize();
	}

	void MapScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::ESC))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::BossBeppi);
		}
		if (KEY_DOWN(eKeyCode::V))
		{
			SceneManager::ChangeScene(eSceneType::BossVegetable);
		}
	}

	void MapScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"MapScene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 50, szFloat, strLen);
	}

	void MapScene::Enter()
	{
	}

	void MapScene::Exit()
	{
	}
}