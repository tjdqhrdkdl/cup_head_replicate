#include "yaBossObject.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{
	BossObject::BossObject()
	{
		SetName(L"BossObject");
		SetPos({ 800,900 });
		SetScale({ 50.0f,30.0f });
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mCollider = new Collider();
		AddComponent(mCollider);


		
	}

	BossObject::~BossObject()
	{
	}

	void BossObject::Tick()
	{
		GameObject::Tick();
	}

	void BossObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossObject::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void BossObject::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void BossObject::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void BossObject::Release()
	{
	}

}