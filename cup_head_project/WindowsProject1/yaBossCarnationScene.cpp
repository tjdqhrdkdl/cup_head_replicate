#include "yaBossCarnationScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaObjectManager.h"
#include "yaCollisionManager.h"
#include "yaTime.h"
#include "yaReady.h"
#include "yaGround.h"
#include "yaLeftWall.h"
#include "yaRightWall.h"
#include "yaUIManager.h"
#include "yaHealthUI.h"
#include "yaKnockOut.h"
#include "yaCameraBlur.h"
#include "yaButton.h"
#include "yaCarnation.h"
#include "yaFlowerPlatForm.h"
#include "yaSound.h"
#include "yaScoreScene.h"
namespace ya
{
	BossCarnationScene::BossCarnationScene()
		:mbInitialized(true)
		, mPhase(1)
	{
	}

	BossCarnationScene::~BossCarnationScene()
	{
	}

	void BossCarnationScene::Initialize()
	{
		mBGM = Resources::Load<Sound>(L"FlowerBGM", L"..\\Resources\\Sound\\Flower\\MUS_Flower.wav");
		mBGM->SetVolume(10);

		SetIntro(true);
		mBGI = new BgImageObject();
		mBGI->SetImage(L"CarnationBackground", L"Cagney Carnation\\Background.png", RGB(255, 0, 255), true);
		AddGameObject(mBGI, eColliderLayer::BackGround);

		Ground* ground = ObjectManager::Instantiate<Ground>(this, eColliderLayer::FrontObject);
		ground->SetPos({ 800,950 });
		ObjectManager::Instantiate<LeftWall>(this, eColliderLayer::FrontObject);
		ObjectManager::Instantiate<RightWall>(this, eColliderLayer::FrontObject);
		mPlayer = ObjectManager::Instantiate<Player>(this, eColliderLayer::Player);
		mPlayer->SetPos({ 400,750 });
		ObjectManager::Instantiate<Ready>(this, eColliderLayer::Top_Effect);
		ObjectManager::Instantiate<FlowerPlatForm>(this, eColliderLayer::FrontObject)->SetPos({ 230,480 });
		ObjectManager::Instantiate<FlowerPlatForm>(this, eColliderLayer::FrontObject)->SetPos({ 590,490 });
		ObjectManager::Instantiate<FlowerPlatForm>(this, eColliderLayer::FrontObject)->SetPos({ 950,500 });

		ObjectManager::Instantiate<Carnation>(this, eColliderLayer::FrontMonster);
		mCameraBlur = ObjectManager::Instantiate<CameraBlur>(this, eColliderLayer::Top_Effect);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::FrontMonster, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::FrontObject, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::BehindMonster, true);
		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Player_Projecttile, true);
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
		KnockOut();


		HUD* healthUI = UIManager::GetUiInstant<HUD>(eUIType::HP);
		healthUI->SetTarget(mPlayer);
		HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
		exPointUI->SetTarget(mPlayer);
		HUD* weaponUI = UIManager::GetUiInstant<HUD>(eUIType::Gun);
		weaponUI->SetTarget(mPlayer);
		weaponUI->InActive();

		Button* resumeButton = UIManager::GetUiInstant<Button>(eUIType::PLAYOPTION_RESUME);
		resumeButton->GetOnClickEvent() = std::bind(&BossCarnationScene::ResumeClickEvent, this);
		Button* retryButton = UIManager::GetUiInstant<Button>(eUIType::PLAYOPTION_RETRY);
		retryButton->GetOnClickEvent() = std::bind(&BossCarnationScene::RetryClickEvent, this);
		Button* exitButton = UIManager::GetUiInstant<Button>(eUIType::PLAYOPTION_EXIT);
		exitButton->GetOnClickEvent() = std::bind(&BossCarnationScene::ExitClickEvent, this);
		mPhaseTimeChecker = 0;
		mPhase = 0;
		mbPhaseChanged = false;
	}

	void BossCarnationScene::Tick()
	{
		if (!Time::isStop())
		{
			Scene::Tick();
			if (mTime < 2)
			{
				mBGM->SetVolume(mTime * 5);
			}
			if (mPhase == 2 && mbPhaseChanged)
			{
				mbPhaseChanged = false;
			}

			if (mPhase == 5 && mbPhaseChanged)
			{
				mbPhaseChanged = false;
				SceneManager::ChangeScene(eSceneType::Win);
				SceneManager::GetScoreScene()->SendInfo(300, mTime, mHPCount, mParryCount, mSuperCount);
			}

		}
		if (KEY_DOWN(eKeyCode::ESC))
		{
			if (!mbUIOn)
			{
				UIManager::Push(eUIType::PLAYOPTION_PANEL);
				mbUIOn = true;
				Time::Stop(true);
				mBGM->Stop(false);
				mCameraBlur->SetOn(true);
			}
			else
			{
				UIManager::Pop(eUIType::PLAYOPTION_PANEL);
				mbUIOn = false;
				mBGM->Play(true);
				Time::Stop(false);
				mCameraBlur->SetOn(false);

			}
		}
	}

	void BossCarnationScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"CarnationScene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 50, szFloat, strLen);
	}

	void BossCarnationScene::ResumeClickEvent()
	{
		if (KEY_DOWN(eKeyCode::LBTN))
		{
			UIManager::Pop(eUIType::PLAYOPTION_PANEL);
			mbUIOn = false;
			Time::Stop(false);
			mCameraBlur->SetOn(false);
		}
	}

	void BossCarnationScene::RetryClickEvent()
	{
		if (KEY_DOWN(eKeyCode::LBTN))
		{
			UIManager::Pop(eUIType::PLAYOPTION_PANEL);
			mbUIOn = false;
			Time::Stop(false);
			mCameraBlur->SetOn(false);
			Scene::Release();
			mbInitialized = false;
			UIManager::Pop(eUIType::HP);
			UIManager::Pop(eUIType::MP);
			HUD* healthUI = UIManager::GetUiInstant<HUD>(eUIType::HP);
			mBGM->SetPosition(0, true);
			healthUI->SetTarget(nullptr);
			HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
			exPointUI->SetTarget(nullptr);
			Initialize();
			Scene::Enter();
			UIManager::Push(eUIType::HP);
			UIManager::Push(eUIType::MP);
		}
	}

	void BossCarnationScene::ExitClickEvent()
	{
		if (KEY_DOWN(eKeyCode::LBTN))
		{
			UIManager::Pop(eUIType::PLAYOPTION_PANEL);
			mbUIOn = false;
			Time::Stop(false);
			mCameraBlur->SetOn(false);
			SceneManager::ChangeScene(eSceneType::Map);
		}
	}

	void BossCarnationScene::Enter()
	{
		Initialize();
		Scene::Enter();
		mBGM->Play(true);
		UIManager::Push(eUIType::Gun);
		UIManager::Push(eUIType::HP);
		UIManager::Push(eUIType::MP);

	}

	void BossCarnationScene::Exit()
	{
		mBGM->Stop(true);
		Scene::Release();
		mbInitialized = false;
		UIManager::Pop(eUIType::HP);
		UIManager::Pop(eUIType::MP);
		UIManager::Pop(eUIType::Gun);
		HUD* healthUI = UIManager::GetUiInstant<HUD>(eUIType::HP);
		healthUI->SetTarget(nullptr);
		HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
		exPointUI->SetTarget(nullptr);
		HUD* weaponUI = UIManager::GetUiInstant<HUD>(eUIType::Gun);
		weaponUI->SetTarget(nullptr);

		Release();
	}

	void ya::BossCarnationScene::BGMOff()
	{
		mBGM->Stop(true);
	}

	void BossCarnationScene::Release()
	{
		Carnation().Release();
	}

}