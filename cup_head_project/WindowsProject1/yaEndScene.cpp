#include "yaEndScene.h"
#include "yaPlayer.h"
#include "yaResources.h"
#include "yaBgImageObject.h"
#include "yaInput.h"
#include "yaScenemanager.h"
#include "yaObjectManager.h"
#include "yaEndBook.h"
#include "yaResources.h"
#include "yaSound.h"
namespace ya 
{
	EndScene::EndScene()
	{
	}

	EndScene::~EndScene()
	{
	}

	void EndScene::Initialize()
	{

		Scene::Initialize();
		ObjectManager::Instantiate<EndBook>(this, eColliderLayer::BackGround)->SetPos({800,900});
		mBGM = Resources::Load<Sound>(L"GoodEnding!", L"..\\Resources\\Sound\\MUS_GoodEnding.wav");
		mBGM->SetVolume(20);

	}

	void EndScene::Tick()
	{
		if (mbStart)
			mBGM->Play(true);
		Scene::Tick();
	}

	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

	}

	void EndScene::Enter()
	{
		Initialize();
		Scene::Enter();
	}

	void EndScene::Exit()
	{
	}
}