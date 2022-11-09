#include "yaMapScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"

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
		if (KEY_DOWN(eKeyCode::B))
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

		Graphics graphic(hdc);
		FontFamily  fontFamily(L"Arial");
		Font        font(&fontFamily, 12, 0, Gdiplus::UnitPoint);
		PointF      pointF(10.0f, 30.0f);
		SolidBrush  solidBrush(Color(255, 0, 0, 0));

		graphic.DrawString(L"MapScene", -1, &font, pointF, &solidBrush);

	}

	void MapScene::Enter()
	{
	}

	void MapScene::Exit()
	{
	}
}