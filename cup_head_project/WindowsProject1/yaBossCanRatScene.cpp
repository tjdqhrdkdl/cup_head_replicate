#include "yaBossCanRatScene.h"
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
#include "yaWernerWermanPh1.h"
#include "yaWernerWermanPh2.h"
#include "yaWernerWermanPh3.h"
#include "yaPhase2BGChanger.h"
#include "yaPhase3BGChanger.h"
#include "yaPhase3BGExplodeEffect.h"
#include "yaCameraBlur.h"
#include "yaButton.h"
namespace ya
{
	BossCanRatScene::BossCanRatScene()
		:mbInitialized(true)
		, mPhase(1)
	{
	}

	BossCanRatScene::~BossCanRatScene()
	{
	}

	void BossCanRatScene::Initialize()
	{
		SetIntro(true);
		mBGIHouse = new BgImageObject();
		mBGI1 = new BgImageObject();
		mBGI2 = new BgImageObject();
		mBGI3_a = new BgImageObject();
		mBGI3_b = new BgImageObject();
		mBGIHouse->SetImage(L"CanRatHouseBGI", L"Werner Werman\\Background\\House BG\\mouse_bg_background.png",RGB(255,0,255), true);
		mBGIHouse->SetPos({ 0,-40 });
		mBGI1->SetImage(L"CanRatPhase1BGI", L"Werner Werman\\Background\\Wall\\Phase 1\\mouse_bg_phase_1_wall.png", RGB(255, 0, 255), true);
		mBGI1->SetPos({ 0,-80 });
		mBGI2->SetImage(L"CanRatPhase2BGI", L"Werner Werman\\Background\\Wall\\Phase 2\\mouse_bg_phase_2_wall.png", RGB(255, 0, 255), true);
		mBGI2->SetPos({ 0,-80 });
		mBGI3_a->SetImage(L"CanRatPhase3aBGI", L"Werner Werman\\Background\\Wall\\Phase 3\\A\\mouse_bg_phase_3_wall_a.png", RGB(255, 0, 255), true);
		mBGI3_a->SetPos({ 0,-80 });
		mBGI3_b->SetImage(L"CanRatPhase3bBGI", L"Werner Werman\\Background\\Wall\\Phase 3\\B\\mouse_bg_phase_3_wall_b.png", RGB(255, 0, 255), true);
		mBGI3_b->SetPos({ 0,-80 });
		AddGameObject(mBGIHouse, eColliderLayer::BackGround);
		mPeakingCat = new PeakingCat({ 0,0 }, { 0,0 });
		mPeakingCat->SetOn(false);
		AddGameObject(mPeakingCat, eColliderLayer::BackGround);
		AddGameObject(mBGI1, eColliderLayer::BackGround);

		Ground* ground = ObjectManager::Instantiate<Ground>(this, eColliderLayer::FrontObject);
		ground->SetPos({ 800,950 });
		ObjectManager::Instantiate<LeftWall>(this, eColliderLayer::FrontObject);
		ObjectManager::Instantiate<RightWall>(this, eColliderLayer::FrontObject);
		mPlayer = ObjectManager::Instantiate<Player>(this, eColliderLayer::Player);
		mPlayer->SetPos({ 400,750 });
		ObjectManager::Instantiate<WernerWermanPh1>(SceneManager::GetCurScene(), eColliderLayer::FrontMonster);
		ObjectManager::Instantiate<Ready>(this, eColliderLayer::Top_Effect);

		mCameraBlur = ObjectManager::Instantiate<CameraBlur>(this, eColliderLayer::Top_Effect);
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
		KnockOut();
		WernerWermanPh2(true, true);
		WernerWermanPh3(true);
		Phase2BGChanger();
		Phase3BGChanger();
		Phase3BGExplodeEffect(); 
		for (size_t i = 0; i < 7; i++)
		{
			Disc* disc = new Disc(false);
			disc->SetPos({ 1800, 130.0f * i + 100 });
			mDiscs[0].push_back(disc);
		}
		for (size_t i = 0; i < 7; i++)
		{
			Disc* disc = new Disc(true);
			disc->SetPos({ -200,130.0f * i + 100 });
			mDiscs[1].push_back(disc);
		}



		HUD* healthUI = UIManager::GetUiInstant<HUD>(eUIType::HP);
		healthUI->SetTarget(mPlayer);
		HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
		exPointUI->SetTarget(mPlayer);
		Button* resumeButton = UIManager::GetUiInstant<Button>(eUIType::PLAYOPTION_RESUME);
		resumeButton->GetOnClickEvent() = std::bind(&BossCanRatScene::ResumeClickEvent, this);
		Button* retryButton = UIManager::GetUiInstant<Button>(eUIType::PLAYOPTION_RETRY);
		retryButton->GetOnClickEvent() = std::bind(&BossCanRatScene::RetryClickEvent, this);
		Button* exitButton = UIManager::GetUiInstant<Button>(eUIType::PLAYOPTION_EXIT);
		exitButton->GetOnClickEvent() = std::bind(&BossCanRatScene::ExitClickEvent, this);
		mPhaseTimeChecker = 0;
		mPhase = 0;
		mbPhaseChanged = false;
	}

	void BossCanRatScene::Tick()
	{
		if (!Time::isStop())
		{
			Scene::Tick();
			if (mPhase < 2)
			{
				mPeakTimeChecker += Time::DeltaTime();
				if (mPeakTimeChecker > 10)
				{
					switch (rand() % 3)
					{
					case 0:
						mPeakingCat->Reset({ -500,800 }, { 400, 640 });
						break;
					case 1:
						mPeakingCat->Reset({ 2100,800 }, { 1150, 250 });
						break;
					case 2:
						mPeakingCat->Reset({ 400,1200 }, { 830, 840 });
						break;
					}

					mPeakTimeChecker = 0;
				}
			}
			else if (mPhase == 2)
			{
				mPeakTimeChecker += Time::DeltaTime();
				if (mPeakTimeChecker > 10)
				{
					switch (rand() % 3)
					{
					case 0:
						mPeakingCat->Reset({ -500,800 }, { 400, 540 });
						break;
					case 1:
						mPeakingCat->Reset({ 2100,800 }, { 1150, 250 });
						break;
					case 2:
						mPeakingCat->Reset({ 400,1200 }, { 830, 840 });
						break;
					}

					mPeakTimeChecker = 0;
				}
			}
			if (mPhase == 2 && mbPhaseChanged)
			{
				ObjectManager::Destroy(mBGI1);
				AddGameObject(mBGI2, eColliderLayer::BehindMonster);
				mPh2BGChanger = ObjectManager::Instantiate<Phase2BGChanger>(this, eColliderLayer::BehindMonster);
				for (size_t i = 0; i < 2; i++)
				{
					for (size_t k = 0; k < 7; k++)
					{
						dynamic_cast<WernerWermanPh2*>(mPhase2Object)->SetDiscs(mDiscs[i][k], i);
					}
				}
				mbPhaseChanged = false;
			}

			if (mPhase == 3 && mbPhaseChanged)
			{
				mPhaseTimeChecker += Time::DeltaTime();
				mPeakingCat->SetPhase2ObjectToDelete(mPhase2Object);
				mbPhaseChanged = false;
			}

			if (mPhase == 5 && mbPhaseChanged)
			{
				mbPhaseChanged = false;
				SceneManager::ChangeScene(eSceneType::Map);
			}
		}
		if (KEY_DOWN(eKeyCode::ESC))
		{
			if (!mbUIOn)
			{
				UIManager::Push(eUIType::PLAYOPTION_PANEL);
				mbUIOn = true;
				Time::Stop(true);
				mCameraBlur->SetOn(true);
			}
			else
			{
				UIManager::Pop(eUIType::PLAYOPTION_PANEL);
				mbUIOn = false;
				Time::Stop(false);
				mCameraBlur->SetOn(false);

			}
		}

	}

	void BossCanRatScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"CanRatScene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 50, szFloat, strLen);



	}

	void BossCanRatScene::ResumeClickEvent()
	{
		if (KEY_DOWN(eKeyCode::LBTN))
		{
			UIManager::Pop(eUIType::PLAYOPTION_PANEL);
			mbUIOn = false;
			Time::Stop(false);
			mCameraBlur->SetOn(false);
		}
	}

	void BossCanRatScene::RetryClickEvent()
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
			healthUI->SetTarget(nullptr);
			HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
			exPointUI->SetTarget(nullptr);
			Initialize();
			Scene::Enter();
			UIManager::Push(eUIType::HP);
			UIManager::Push(eUIType::MP);
		}
	}

	void BossCanRatScene::ExitClickEvent()
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

	void BossCanRatScene::ChangeBGQue()
	{
		ObjectManager::Destroy(mBGI2);
		ObjectManager::Destroy(mPh2BGChanger);
		dynamic_cast<Phase2BGChanger*>(mPh2BGChanger)->DestroyGround();
		AddGameObject(mBGI3_a, eColliderLayer::FrontObject);
		ObjectManager::Instantiate<Phase3BGChanger>(this, eColliderLayer::FrontObject);
	}
	void BossCanRatScene::ChangeLastBGQue()
	{
		ObjectManager::Destroy(mBGI3_a);
		AddGameObject(mBGI3_b, eColliderLayer::FrontObject);
		ObjectManager::Instantiate<Phase3BGExplodeEffect>(this, eColliderLayer::Effect);
	}
	void BossCanRatScene::Enter()
	{
		Initialize();
		Scene::Enter();
		UIManager::Push(eUIType::HP);
		UIManager::Push(eUIType::MP);
	}

	void BossCanRatScene::Exit()
	{
		Scene::Release();
		mbInitialized = false;
		UIManager::Pop(eUIType::HP);
		UIManager::Pop(eUIType::MP);
		HUD* healthUI = UIManager::GetUiInstant<HUD>(eUIType::HP);
		healthUI->SetTarget(nullptr);
		HUD* exPointUI = UIManager::GetUiInstant<HUD>(eUIType::MP);
		exPointUI->SetTarget(nullptr);

		for (size_t i = 0; i < 2; i++)
		{
			mDiscs[i].clear();
		}
		Release();
	}
	void BossCanRatScene::Release()
	{
		WernerWermanPh1().Release();
		WernerWermanPh2(1,true).Release();
		WernerWermanPh3(true).Release();
		Phase2BGChanger().Release();
		Phase3BGChanger().Release();
		Phase3BGExplodeEffect().Release();
	}
}