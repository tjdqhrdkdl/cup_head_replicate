#include "yaPhase2BGChanger.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"
#include "yaPh2WallGround.h"

namespace ya
{
	Phase2BGChanger::Phase2BGChanger()
	{
		SetName(L"Phase2BGChanger");
		SetPos({ 842,1040 });

		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Phase2BGChanger", L"..\\Resources\\Image\\Werner Werman\\Background\\Ph2 Platform\\mouse_bg_phase2_platform_00", 10, 0.1f, false, false);

		mAnimator->GetCompleteEvent(L"Phase2BGChanger") = std::bind(&Phase2BGChanger::Phase2BGChangerCompleteEvent, this);
		mAnimator->Play(L"Phase2BGChanger", false);
	}

	Phase2BGChanger::~Phase2BGChanger()
	{
	}

	void Phase2BGChanger::Tick()
	{
		GameObject::Tick();
	}

	void Phase2BGChanger::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Phase2BGChanger::DestroyGround()
	{
		ObjectManager::Destroy(mPh2WallGround);
		dynamic_cast<Ph2WallGround*>(mPh2WallGround)->FreePlayers();
	}


	void Phase2BGChanger::Phase2BGChangerCompleteEvent()
	{
		mPh2WallGround = ObjectManager::Instantiate<Ph2WallGround>(SceneManager::GetCurScene(), eColliderLayer::FrontObject);
	}

	void Phase2BGChanger::Release()
	{
		mAnimator->Release();
	}

}