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
#include "yaUIManager.h"
#include "yaButton.h"
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
		mBGI->SetPos({ 200,0 });
		AddGameObject(mBGI, eColliderLayer::BackGround);

		Scene::Initialize();
		Button* startButton = UIManager::GetUiInstant<Button>(eUIType::TITLEOPTION_START);
		startButton->GetOnClickEvent() = std::bind(&TitleScene::StartClickEvent, this);
		Button* exitButton = UIManager::GetUiInstant<Button>(eUIType::TITLEOPTION_EXIT);
		exitButton->GetOnClickEvent() = std::bind(&TitleScene::ExitClickEvent, this);
	}

	void TitleScene::Tick()
	{
		Scene::Tick();

	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void TitleScene::StartClickEvent()
	{
		if (KEY_DOWN(eKeyCode::LBTN))
			SceneManager::ChangeScene(eSceneType::Map);
	}

	void TitleScene::ExitClickEvent()
	{
	}

	void TitleScene::Enter()
	{
		UIManager::Push(eUIType::TITLEOPTION_START);
		UIManager::Push(eUIType::TITLEOPTION_OPTION);
		UIManager::Push(eUIType::TITLEOPTION_EXIT);
	}

	void TitleScene::Exit()
	{
		UIManager::Pop(eUIType::TITLEOPTION_START);
		UIManager::Pop(eUIType::TITLEOPTION_OPTION);
		UIManager::Pop(eUIType::TITLEOPTION_EXIT);
	}
}