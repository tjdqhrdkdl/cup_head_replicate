#include "yaTomatoFire.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaGround.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaObjectManager.h"

namespace ya 
{
	TomatoFire::TomatoFire(bool right)
	{
		SetName(L"TomatoBombFire");
		SetScale({ 100.0f,20.0f });

		Collider* col = new Collider();
		AddComponent(col);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"MoveLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cherry Bomb\\Fire\\mouse_cherrybomb_fire_00", 10, 0.04f, false, false);
		mAnimator->CreateAnimation(L"MoveRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cherry Bomb\\Fire\\mouse_cherrybomb_fire_00", 10, 0.04f, false, true);
		if (right)
			mAnimator->Play(L"MoveRight", false);
		else
			mAnimator->Play(L"MoveLeft", false);

	}

	TomatoFire::~TomatoFire()
	{
	}

	void TomatoFire::Tick()
	{
		Vector2 pos = GetPos();
		GameObject::Tick();
		if (mAnimator->GetPlayAnimation()->GetName() == L"MoveRight")
			pos.x += 800 * Time::DeltaTime();
		else
			pos.x -= 800 * Time::DeltaTime();

		if (pos.x > 2000 or pos.x < -400)
			ObjectManager::Destroy(this);
		SetPos(pos);
	}

	void TomatoFire::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void TomatoFire::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void TomatoFire::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void TomatoFire::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void TomatoFire::Release()
	{
		mAnimator->Release();
	}

}