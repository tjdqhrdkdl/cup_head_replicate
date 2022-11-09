#include "yaLogoScene.h"
#include "yaResources.h"
#include "yaLogoObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaEnemy.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaTime.h"
namespace ya {
	LogoScene::LogoScene()
		:mSceneTime(6.0f)
		,mSceneTimeChecker(0.0f)
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{
		ObjectManager::Instantiate<LogoObject>(this, eColliderLayer::BackGround);
		Scene::Initialize();
	}

	void LogoScene::Tick()
	{
		Scene::Tick();
		mSceneTimeChecker += Time::DeltaTime();
		if ((mSceneTimeChecker > mSceneTime) or KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);

		}

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