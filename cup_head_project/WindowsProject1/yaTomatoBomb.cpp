#include "yaTomatoBomb.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaGround.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaWernerWermanPh1.h"
#include "yaObjectManager.h"
#include "yaTomatoFire.h"
namespace ya
{
	TomatoBomb::TomatoBomb(bool right)
	{
		mbRight = right;
		SetName(L"TomatoBomb");
		SetScale({ 100.0f,100.0f });

		Collider* col = new Collider();
		AddComponent(col);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"FlipLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cherry Bomb\\Normal\\mouse_cherrybomb_00", 8, 0.04f, false, false);
		mAnimator->CreateAnimation(L"FlipRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cherry Bomb\\Normal\\mouse_cherrybomb_00", 8, 0.04f, false, true);
		mAnimator->CreateAnimation(L"Explode", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Cherry Bomb\\Explode\\mouse_cherrybomb_explode_00", 8, 0.04f, false, false);

		mAnimator->GetCompleteEvent(L"Explode") = std::bind(&TomatoBomb::ExplodeCompleteEvent, this);

		switch (rand()%5)
		{
		case 0:
			mDegree = -60;
			break;
		case 1:
			mDegree = -74;
			break;
		case 2:
			mDegree = -50;
			break;
		case 3:
			mDegree = -70;
			break;
		case 4:
			mDegree = -80;
			break;
		}

		if (right)
			mAnimator->Play(L"FlipRight", true);
		else
			mAnimator->Play(L"FlipLeft", true);

	}

	TomatoBomb::~TomatoBomb()
	{
	}

	void TomatoBomb::Tick()
	{
		Vector2 pos = GetPos();

		if (mAnimator->GetPlayAnimation()->GetName() == L"FlipLeft" or mAnimator->GetPlayAnimation()->GetName() == L"FlipRight")
		{
			mDegree -= 100 * Time::DeltaTime();
			if (mDegree < -140)
				mDegree += 50 * Time::DeltaTime();
			if (mDegree < -180)
				mDegree = -180;
			if (mbRight)
			{
				pos.x -= math::Rotate(Vector2::Up, mDegree).x * 800 * Time::DeltaTime();
				pos.y += math::Rotate(Vector2::Up, mDegree).y * 800 * Time::DeltaTime();
			}
			else
			{
				pos += math::Rotate(Vector2::Up, mDegree) * 800 * Time::DeltaTime();
			}
		}
		SetPos(pos);
		GameObject::Tick();
	}

	void TomatoBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void TomatoBomb::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			Vector2 pos = GetPos();
			pos.y = 750;
			SetPos(pos);
			mAnimator->Play(L"Explode", false);
			TomatoFire* lFire = new TomatoFire(false);
			TomatoFire* rFire = new TomatoFire(true);
			lFire->SetPos(GetPos());
			rFire->SetPos(GetPos());
			SceneManager::GetCurScene()->AddGameObject(lFire, eColliderLayer::Monster_Projecttile);
			SceneManager::GetCurScene()->AddGameObject(rFire, eColliderLayer::Monster_Projecttile);
			GetComponent<Collider>()->SetOff(true);
		}
	}

	void TomatoBomb::OnCollisonStay(Collider* other, Collider* my)
	{
	}



	void TomatoBomb::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void TomatoBomb::ExplodeCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

	void TomatoBomb::Release()
	{
		mAnimator->Release();
		TomatoFire().Release();
	}

}