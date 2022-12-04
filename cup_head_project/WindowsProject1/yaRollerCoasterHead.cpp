#include "yaRollerCoasterHead.h"
#include "yaObjectManager.h"
#include "yaSceneManager.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"

namespace ya
{
	RollerCoasterHead::RollerCoasterHead()
		:
		 mAliveTime(13.0f)
		, mAliveTimeChecker(0)
	{
		SetName(L"CoasterTail");
		SetScale({ 270,200 });

		mCollider = new Collider();
		mCollider->SetAddPos({ 30,-30 });
		AddComponent(mCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->SetLightenAnimation(mAnimator->CreateAnimation(L"PinkIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\PinkHead\\Rollercoaster_Front_", 8, 0.04f, true, false, { 0,0 }),
			mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Front_", 8, 0.04f, true, false, { 0,0 }));
		mAnimator->Play(L"PinkIdle", true);

		mPinkNose = new RollerCoasterHeadPinkNose();
		SceneManager::GetCurScene()->AddGameObject(mPinkNose, eColliderLayer::FrontMonster);
	}

	RollerCoasterHead::~RollerCoasterHead()
	{
	}

	void RollerCoasterHead::Tick()
	{
		if (mPinkNose != nullptr) 
		{
			mPinkNose->SetPos(GetPos());
			if (mPinkNose->isParried())
				mAnimator->SetLighten(true);
		}

		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
			ObjectManager::Destroy(this);
		GameObject::Tick();
	}

	void RollerCoasterHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void RollerCoasterHead::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void RollerCoasterHead::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void RollerCoasterHead::OnCollisonExit(Collider* other, Collider* my)
	{
	}

}