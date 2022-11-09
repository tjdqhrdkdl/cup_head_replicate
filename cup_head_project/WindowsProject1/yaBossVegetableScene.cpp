#include "yaBossVegetableScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
namespace ya {
	BossVegetableScene::BossVegetableScene()
	{
	}

	BossVegetableScene::~BossVegetableScene()
	{
	}

	void BossVegetableScene::Initialize()
	{

		AddGameObject(new Player(), eColliderLayer::Player);
		Scene::Initialize();
	}

	void BossVegetableScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Map);
		}
	}

	void BossVegetableScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Graphics graphic(hdc);
		FontFamily  fontFamily(L"Arial");
		Font        font(&fontFamily, 12, 0, Gdiplus::UnitPoint);
		PointF      pointF(10.0f, 30.0f);
		SolidBrush  solidBrush(Color(255, 0, 0, 0));

		graphic.DrawString(L"BossVegetableScene", -1, &font, pointF, &solidBrush);

	}

	void BossVegetableScene::Enter()
	{
	}

	void BossVegetableScene::Exit()
	{
	}
}