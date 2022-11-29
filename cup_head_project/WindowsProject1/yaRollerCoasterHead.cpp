#include "yaRollerCoasterHead.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	RollerCoasterHead::RollerCoasterHead()
	{
		SetName(L"CoasterTail");
		SetScale({ 270,200 });

		mCollider = new Collider();
		mCollider->SetAddPos({ 30,-30 });
		AddComponent(mCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Rollercoaster\\Rollercoaster_Front_", 8, 0.04f, true, false, { 0,0 });
		
		mAnimator->Play(L"Idle", true);
	}

	RollerCoasterHead::~RollerCoasterHead()
	{
	}

	void RollerCoasterHead::Tick()
	{
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