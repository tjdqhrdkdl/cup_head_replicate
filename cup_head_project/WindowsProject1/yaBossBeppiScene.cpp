#include "yaBossBeppiScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaObjectManager.h"
#include "yaBeppiPhaseOne.h"
#include "yaCollisionManager.h"

namespace ya 
{
	BossBeppiScene::BossBeppiScene()
		:mScenePlaying(false)
	{
	}

	BossBeppiScene::~BossBeppiScene()
	{
	}

	void BossBeppiScene::Initialize()
	{
		mBGI = new BgImageObject();
		mBGI->SetImage(L"BeppiMainBGI", L"Beppi\\clown_bg_main.png");
		mBGI->SetPos({ -200,-70 });
		AddGameObject(mBGI, eColliderLayer::BackGround);
		ObjectManager::Instantiate<Player>(this, eColliderLayer::Player);

		ObjectManager::Instantiate<BeppiPhaseOne>(this, Vector2(1000.0f, 700.0f), eColliderLayer::Monster);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster, true);
		CollisionManager::SetLayer(eColliderLayer::Player_Projecttile, eColliderLayer::Monster, true);
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

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"BossBeppiScene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 50, szFloat, strLen);

	}

	void BossBeppiScene::Enter()
	{
	}

	void BossBeppiScene::Exit()
	{
	}
}