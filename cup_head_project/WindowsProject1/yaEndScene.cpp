#include "yaEndScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaObjectManager.h"
#include "yaEndBook.h"
namespace ya {
	EndScene::EndScene()
	{
	}

	EndScene::~EndScene()
	{
	}

	void EndScene::Initialize()
	{

		Scene::Initialize();
		ObjectManager::Instantiate<EndBook>(this, eColliderLayer::BackGround)->SetPos({800,900});

	}

	void EndScene::Tick()
	{
		Scene::Tick();
	}

	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Graphics graphic(hdc);
		FontFamily  fontFamily(L"Arial");
		Font        font(&fontFamily, 12, 0, Gdiplus::UnitPoint);
		PointF      pointF(10.0f, 30.0f);
		SolidBrush  solidBrush(Color(255, 0, 0, 0));

		graphic.DrawString(L"EndScene", -1, &font, pointF, &solidBrush);

	}

	void EndScene::Enter()
	{
		Initialize();
		Scene::Enter();
	}

	void EndScene::Exit()
	{
	}
}