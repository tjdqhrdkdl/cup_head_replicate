#include "yaMapScene.h"
#include "yaWorldPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaUIManager.h"
#include "yaCamera.h"
#include "yaCollisionManager.h"
#include "yaWorldMap.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaBossObject.h"
#include "yaSound.h"
namespace ya {
	MapScene::MapScene()
	{
	}

	MapScene::~MapScene()
	{
	}

	void MapScene::Initialize()
	{
		mbStart = true;

		mBGM = Resources::Load<Sound>(L"WorldMapBGM", L"..\\Resources\\Sound\\Map\\bgm_map_world_1.wav");
		mWorldMap = new WorldMap();
		mWorldPlayer = new WorldPlayer();
		mWorldMap->SetPlayer(mWorldPlayer);
		mBGI = new BgImageObject();
		mBGI->SetImage(L"WorldMapBGI", L"Map\\world1_large_island_main.png", RGB(255, 0, 255), true);
		mBGI->SetPos({ 0,0 });
		mBGITopperLeft = new BgImageObject();
		mBGITopperLeft->SetImage(L"WorldMapTopperLeftBGI", L"Map\\Toppers\\Left\\world1_top_level_pieces_01.png", RGB(255, 0, 255), true);
		mBGITopperLeft->SetPos({ 558,430 });
		mBGITopperRight = new BgImageObject();
		mBGITopperRight->SetImage(L"WorldMapTopperRightBGI", L"Map\\Toppers\\Right\\world1_top_level_pieces_02.png", RGB(255, 0, 255), true);
		mBGITopperRight->SetPos({ 2138,270 });
		AddGameObject(mWorldMap, eColliderLayer::BackGround);
		AddGameObject(mBGI, eColliderLayer::BackGround);
		AddGameObject(mWorldPlayer, eColliderLayer::Player);
		AddGameObject(mBGITopperLeft, eColliderLayer::Top_Effect);
		AddGameObject(mBGITopperRight, eColliderLayer::Top_Effect);

		BossObject* wernerwermanObj = new BossObject();
		wernerwermanObj->mType = eBossType::WernerWerman;
		wernerwermanObj->GetAnimator()->CreateAnimation(L"wernerwermanObj", L"..\\Resources\\Image\\Werner Werman\\MurineCorps\\tile0", 3, 0.1f, true, false);
		wernerwermanObj->GetAnimator()->Play(L"wernerwermanObj", true);
		wernerwermanObj->SetPos({ 3950,1460 });
		wernerwermanObj->SetScale({ 70,100 });
		wernerwermanObj->GetCollider()->SetAddPos({ -120,-100 });

		BossObject* carnationObj = new BossObject();
		carnationObj->mType = eBossType::Carnation;
		carnationObj->GetAnimator()->CreateAnimation(L"carnationObj", L"..\\Resources\\Image\\Cagney Carnation\\CagneyObject\\tile0", 3, 0.1f, true, false);
		carnationObj->GetAnimator()->Play(L"carnationObj", true);
		carnationObj->SetPos({ 2200,880});
		carnationObj->SetScale({ 150,70 });
		carnationObj->GetCollider()->SetAddPos({ 0,-35 });


		BossObject* beppiObj = new BossObject();
		beppiObj->mType = eBossType::Beppi;
		beppiObj->GetAnimator()->CreateAnimation(L"beppiObj", L"..\\Resources\\Image\\Beppi\\BeppiObj\\tile0", 3, 0.1f, true, false);
		beppiObj->GetAnimator()->Play(L"beppiObj", true);
		beppiObj->SetPos({ 1400,1000 });
		beppiObj->SetScale({ 60,70 });
		beppiObj->GetCollider()->SetAddPos({ -45,-80 });
		Collider* midCol = new Collider();
		midCol->SetAddPos({ 0,-50 });
		Collider* botCol = new Collider();
		botCol->SetAddPos({ 45,-20 });
		beppiObj->AddComponent(midCol);
		beppiObj->AddComponent(botCol);

		AddGameObject(wernerwermanObj, eColliderLayer::FrontObject);
		AddGameObject(beppiObj, eColliderLayer::FrontObject);
		AddGameObject(carnationObj, eColliderLayer::FrontObject);


		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::FrontObject, true);


		Scene::Initialize();
	}

	void MapScene::Tick()
	{
		if (mTime < 2)
		{
			mBGM->SetVolume(mTime * 25);
		}
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::ESC))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
		if (KEY_DOWN(eKeyCode::B))
		{
			SceneManager::ChangeScene(eSceneType::BossBeppi);
		}
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::BossWernerWerman);
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			SceneManager::ChangeScene(eSceneType::BossCarnation);
		}
		if (KEY_DOWN(eKeyCode::Q))
		{
			SceneManager::ChangeScene(eSceneType::End);
		}
		if (mWorldPlayer->GetEnterObject() != nullptr)
		{
			if (KEY_DOWN(eKeyCode::Z)) 
			{
				BossObject* bossObj = dynamic_cast<BossObject*>(mWorldPlayer->GetEnterObject());
				if (bossObj != nullptr && bossObj->mType == eBossType::WernerWerman)
				{
					SceneManager::ChangeScene(eSceneType::BossWernerWerman);
				}
				else if (bossObj != nullptr && bossObj->mType == eBossType::Beppi)
				{
					SceneManager::ChangeScene(eSceneType::BossBeppi);
				}
				else if (bossObj != nullptr && bossObj->mType == eBossType::Carnation)
				{
					SceneManager::ChangeScene(eSceneType::BossCarnation);
				}

			}
		}
		if (KEY_DOWN(eKeyCode::N_1))
		{
			mBGI->SetOff(true);
		}
		if (KEY_DOWN(eKeyCode::N_2))
		{
			mBGI->SetOff(false);
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
		Camera::SetTarget(mWorldPlayer);
		mBGM->Play(true);
	}

	void MapScene::Exit()
	{
		Camera::PositionInit();
		mBGM->Stop(true);
	}
}