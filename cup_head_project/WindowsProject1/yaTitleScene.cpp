#include "yaTitleScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaBeppiPhaseOne.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaTime.h"
namespace ya 
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		mBGI = new BgImageObject();
		mBGI->SetImage(L"TitleMainMenuBGI", L"Main Menu Background.png");
		mBGI->SetPos({ 200,-150 });
		AddGameObject(mBGI, eColliderLayer::BackGround);

		Scene::Initialize();
	}

	void TitleScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Map);
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);


	}

	void TitleScene::Enter()
	{
	}

	void TitleScene::Exit()
	{
	}
}