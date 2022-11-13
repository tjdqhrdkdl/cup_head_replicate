#include "yaLogoScene.h"
#include "yaResources.h"
#include "yaLogoAnimation.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaEnemy.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaReadyAnimation.h"
namespace ya {
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{
		ObjectManager::Instantiate<ReadyAnimation>(this, eColliderLayer::BackGround);
		ObjectManager::Instantiate<LogoAnimation>(this, eColliderLayer::BackGround);
		Scene::Initialize();
	}

	void LogoScene::Tick()
	{
		Scene::Tick();
		bool out = false;
		for (size_t i = 0; i < 58; i++)
		{
			if (KEY_DOWN((eKeyCode)i))
			{
				out = true;
			}
		}
		if (out)
			SceneManager::ChangeScene(eSceneType::Title);
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		Graphics graphic(hdc);
		FontFamily  fontFamily(L"Arial");
		Font        font(&fontFamily, 12,0, Gdiplus::UnitPoint);
		PointF      pointF(10.0f, 30.0f);
		SolidBrush  solidBrush(Color(255, 0, 0, 0));

		graphic.DrawString(L"LogoScene", -1, &font, pointF, &solidBrush);

	}

	void LogoScene::Enter()
	{
	}

	void LogoScene::Exit()
	{
	}
}