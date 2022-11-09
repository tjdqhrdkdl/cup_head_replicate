#include "yaTitleScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaEnemy.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
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
		mBGI->SetImage(L"TitleBGI", L"Title Screen\\Background\\title_screen_background.png");
		AddGameObject(mBGI, eColliderLayer::BackGround);
		ObjectManager::Instantiate<Player>(this, eColliderLayer::Player);
		ObjectManager::Instantiate<Enemy>(this, Vector2(1000.0f, 580.0f), eColliderLayer::Monster);
		ObjectManager::Instantiate<Enemy>(this, Vector2(100.0f, 580.0f), eColliderLayer::Monster);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster, true);
		CollisionManager::SetLayer(eColliderLayer::Player_Projecttile, eColliderLayer::Monster, true);
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