#include "yaLogoScene.h"
#include "yaResources.h"
#include "yaLogoAnimation.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaBeppiPhaseOne.h"
#include "yaCollisionManager.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaReadyAnimation.h"
#include "yaAnimator.h"
#include "yaBgImageObject.h"
#include "yaSound.h"
namespace ya {
	LogoScene::LogoScene()
	{
	}

	LogoScene::~LogoScene()
	{
	}

	void LogoScene::Initialize()
	{
		mbStart = true;

		mBGM = Resources::Load<Sound>(L"LogoSceneBGM", L"..\\Resources\\Sound\\Logo\\MUS_Intro.wav");
		mBGM->SetVolume(20);
		mReady = ObjectManager::Instantiate<ReadyAnimation>(this, eColliderLayer::BackGround);
		BgImageObject* press =  new BgImageObject();
		press->SetImage(L"PressAny", L"UI\\press.png", RGB(255, 0, 255), true);
		press->SetPos({ 550,760 });
		AddGameObject(press, eColliderLayer::BackGround);
		mLogo = ObjectManager::Instantiate<LogoAnimation>(this, eColliderLayer::BackGround);
		Scene::Initialize();
	}

	void LogoScene::Tick()
	{
		Scene::Tick();
		if (mTime < 2)
		{
			mBGM->SetVolume(mTime * 10);
		}
		bool out = false;
		if (mbReady)
		{
			for (size_t i = 0; i < 58; i++)
			{
				if (KEY_DOWN((eKeyCode)i))
				{
					out = true;
				}
			}
		}
		if (out)
			SceneManager::ChangeScene(eSceneType::Title);
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);


	}

	void LogoScene::Enter()
	{
		mBGM->SetPosition(1.0, true);
	}

	void LogoScene::Exit()
	{
		mReady->GetComponent<Animator>()->DeleteBitmap();
		mLogo->GetComponent<Animator>()->DeleteBitmap();
		ObjectManager::Destroy(mReady);
		ObjectManager::Destroy(mLogo);
		mBGM->Stop(true);

	}
}