#include "yaBossBeppiScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
namespace ya {
	BossBeppiScene::BossBeppiScene()
	{
	}

	BossBeppiScene::~BossBeppiScene()
	{
	}

	void BossBeppiScene::Initialize()
	{

		AddGameObject(new Player(), eColliderLayer::Player);
		Scene::Initialize();
	}

	void BossBeppiScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Map);
		}
	}

	void BossBeppiScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Graphics graphic(hdc);
		FontFamily  fontFamily(L"Arial");
		Font        font(&fontFamily, 12, 0, Gdiplus::UnitPoint);
		PointF      pointF(10.0f, 30.0f);
		SolidBrush  solidBrush(Color(255, 0, 0, 0));

		graphic.DrawString(L"BossBeppiScene", -1, &font, pointF, &solidBrush);

	}

	void BossBeppiScene::Enter()
	{
	}

	void BossBeppiScene::Exit()
	{
	}
}