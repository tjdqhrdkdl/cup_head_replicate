#include "yaBossBeppiScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaObjectManager.h"
#include "yaBeppiPhaseOne.h"
#include "yaCollisionManager.h"
#include "yaTime.h"
#include "yaReady.h"
#include "yaGround.h"
#include "yaLeftWall.h"
#include "yaRightWall.h"
#include "yaUIManager.h"
#include "yaHealthUI.h"
#include "yaBeppiPhaseTwo.h"
#include "yaBeppiPhaseThree.h"
#include "yaBeppiPhaseFour.h"
#include "yaKnockOut.h"
namespace ya 
{
	BossBeppiScene::BossBeppiScene()
		:mbInitialized(true)
		,mPhase(1)
	{
	}

	BossBeppiScene::~BossBeppiScene()
	{
	}

	void BossBeppiScene::Initialize()
	{
		SetIntro(true);
		mBGI = new BgImageObject();
		mBGI->SetImage(L"BeppiMainBGI", L"Beppi\\clown_bg_main.png");
		mBGI->SetPos({ 0,0 });
		AddGameObject(mBGI, eColliderLayer::BackGround);
		BgImageObject* track = new BgImageObject();
		track->SetImage(L"BeppiTrack", L"Beppi\\clown_bg_track.png", RGB(255,0,255), true);
		track->SetPos({ -10,600 });
		AddGameObject(track, eColliderLayer::FrontObject);

		ObjectManager::Instantiate<Ground>(this, eColliderLayer::FrontObject);
		ObjectManager::Instantiate<LeftWall>(this, eColliderLayer::FrontObject);
		ObjectManager::Instantiate<RightWall>(this, eColliderLayer::FrontObject);
		mPlayer = ObjectManager::Instantiate<Player>(this, eColliderLayer::Player);
		ObjectManager::Instantiate<BeppiPhaseOne>(SceneManager::GetCurScene(), eColliderLayer::FrontMonster);
		ObjectManager::Instantiate<Ready>(this, eColliderLayer::Top_Effect);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::FrontMonster, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::FrontObject, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::BehindMonster, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster_Projecttile, true);
		CollisionManager::SetLayer(eColliderLayer::Player_Projecttile, eColliderLayer::FrontMonster, true);
		CollisionManager::SetLayer(eColliderLayer::Player_Projecttile, eColliderLayer::FrontObject, true);
		CollisionManager::SetLayer(eColliderLayer::Player_Projecttile, eColliderLayer::BehindMonster, true);

		CollisionManager::SetLayer(eColliderLayer::FrontMonster, eColliderLayer::FrontObject, true);
		CollisionManager::SetLayer(eColliderLayer::FrontMonster, eColliderLayer::FrontMonster, true);
		CollisionManager::SetLayer(eColliderLayer::Monster_Projecttile, eColliderLayer::FrontObject, true);



		Scene::Initialize();
		mPhase = 1;
		//Initialize
		BeppiPhaseTwo();
		BeppiPhaseThree(true);
		BeppiPhaseFour(true);
		KnockOut();

		HUD* healthUI = UIManager::GetUiInstant<HUD>(eUIType::HP);
		healthUI->SetTarget(mPlayer);
		HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
		exPointUI->SetTarget(mPlayer);
		mPhaseTimeChecker = 0;
		mPhase = 0;
		mbPhaseChanged = false;
	}

	void BossBeppiScene::Tick()
	{
		Scene::Tick();
		if (mPhase == 2 && mbPhaseChanged)
		{
			mPhaseTimeChecker += Time::DeltaTime();
			if (mPhaseTimeChecker > 5.0f)
			{
				BeppiPh2Body* ph2Body = ObjectManager::Instantiate<BeppiPh2Body>(SceneManager::GetCurScene(), eColliderLayer::BehindMonster);
				BeppiPhaseTwo* beppiPh2  = ObjectManager::Instantiate<BeppiPhaseTwo>(this, eColliderLayer::BehindMonster);
				beppiPh2->SetBody(ph2Body);
				mbPhaseChanged = false;
				mPhaseTimeChecker = 0;
			}
		}

		if (mPhase == 3 && mbPhaseChanged)
		{
			mPhaseTimeChecker += Time::DeltaTime();
			if (mPhaseTimeChecker > 8.0f)
			{
				ObjectManager::Instantiate<BeppiPhaseThree>(SceneManager::GetCurScene(), eColliderLayer::FrontMonster);
				mbPhaseChanged = false;
				mPhaseTimeChecker = 0;
			}
		}

		if (mPhase == 4 && mbPhaseChanged)
		{
			mPhaseTimeChecker += Time::DeltaTime();
			if (mPhaseTimeChecker > 18.0f)
			{
				ObjectManager::Instantiate<BeppiPhaseFour>(SceneManager::GetCurScene(), eColliderLayer::BehindMonster);
				mbPhaseChanged = false;
				mPhaseTimeChecker = 0;
			}
		}

		if (mPhase == 5 && mbPhaseChanged)
		{
			mbPhaseChanged = false;
			SceneManager::ChangeScene(eSceneType::Map);
		}

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
		Initialize();
		Scene::Enter();
		UIManager::Push(eUIType::HP);
		UIManager::Push(eUIType::MP);
	}

	void BossBeppiScene::Exit()
	{
		Scene::Release();
		mbInitialized = false;
		UIManager::Pop(eUIType::HP);
		UIManager::Pop(eUIType::MP);
		HUD* healthUI = UIManager::GetUiInstant<HUD>(eUIType::HP);
		healthUI->SetTarget(nullptr);
		HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
		exPointUI->SetTarget(nullptr);
		Release();
	}
	void BossBeppiScene::Release()
	{
		BeppiPhaseOne().Release();
		BeppiPhaseTwo().Release();
		BeppiPhaseThree(true).Release();
		BeppiPhaseFour(true).Release();
	}
}