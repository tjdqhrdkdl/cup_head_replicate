#include "yaRollerCoasterTail.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	RollerCoasterTail::RollerCoasterTail()
	{
		SetName(L"CoasterTail");
		SetScale({ 270,70 });
		mCollider = new Collider();
		Collider* collider2 = new Collider();
		collider2->SetScale({ 50, 170 });
		collider2->SetAddPos({ -100,-50 });
		AddComponent(mCollider);
		AddComponent(collider2);

		mBackAnimator = new Animator();
		mFrontAnimator = new Animator();
		AddComponent(mBackAnimator);
		AddComponent(mFrontAnimator);

		mBackAnimator->CreateAnimation(L"BackIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Back_", 3, 0.1f, true, false, { -20,-20 });
		mFrontAnimator->CreateAnimation(L"FrontIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Back2_", 3, 0.1f, true, false, { 20,20 });
		
		mBackAnimator->Play(L"BackIdle", true);
		mFrontAnimator->Play(L"FrontIdle", true);
		mBackAnimator->DeleteGDIPlusImage();
		mFrontAnimator->DeleteGDIPlusImage();
	}

	RollerCoasterTail::~RollerCoasterTail()
	{
	}

	void RollerCoasterTail::Tick()
	{
		GameObject::Tick();
	}

	void RollerCoasterTail::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void RollerCoasterTail::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void RollerCoasterTail::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void RollerCoasterTail::OnCollisonExit(Collider* other, Collider* my)
	{
	}

}