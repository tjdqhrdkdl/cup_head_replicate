#include "yaCatPaw.h"
#include "yaCollider.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaCamera.h"
#include "yaObjectManager.h"
namespace ya {
	Paw::Paw(bool right)
	{
		mbRight = right;
		SetName(L"CatPaw");
		SetScale({ 1000,200 });

		mCollider = new Collider();
		AddComponent(mCollider);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"PawMainRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Paw\\Main\\cat_paw_main_00", 5, 0.1f, false, false);
		mAnimator->CreateAnimation(L"PawMainLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Paw\\Main\\cat_paw_main_00", 5, 0.1f, false, true);
		mAnimator->CreateAnimation(L"PawOutroRight", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Paw\\Outro\\cat_paw_outro_00", 8, 0.05f, false, false);
		mAnimator->CreateAnimation(L"PawOutroLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 3\\Claw\\Paw\\Outro\\cat_paw_outro_00", 8, 0.05f, false, true);


		mAnimator->GetCompleteEvent(L"PawMainRight") = std::bind(&Paw::PawMainCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PawMainLeft") = std::bind(&Paw::PawMainCompleteEvent, this);


		if (mbRight)
			mAnimator->Play(L"PawMainRight", true);
		else
			mAnimator->Play(L"PawMainLeft", true);

	}

	Paw::~Paw()
	{
	}

	void Paw::Tick()
	{
		Vector2 pos = GetPos();
		GameObject::Tick();
		if(mAnimator->GetPlayAnimation()->GetName() == L"PawMainRight"
			|| mAnimator->GetPlayAnimation()->GetName() == L"PawMainLeft")
		{
			if (mbRight)
				pos.x += Time::DeltaTime() * 600;
			else
				pos.x -= Time::DeltaTime() * 600;

		}

		else
		{
			if (mbRight)
			{
				pos.x -= Time::DeltaTime() * 800;
				if (pos.x < -800)
				{
					mOwnerCat->PawOutroFin();
					ObjectManager::Destroy(this);
				}
			}
			else
			{
				pos.x += Time::DeltaTime() * 800;
				if (pos.x > 2400)
				{
					mOwnerCat->PawOutroFin();
					ObjectManager::Destroy(this);
				}
			}

		}
		SetPos(pos);
	}

	void Paw::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Paw::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void Paw::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Paw::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Paw::PawMainCompleteEvent()
	{
		mHitCount++;
		if (mHitCount == 1)
		{
			mOwnerCat->SummonWoodPieces(mbRight);
			Camera::SetShake(true);
		}
		if (mHitCount > 4)
		{
			if (mbRight)
				mAnimator->Play(L"PawOutroRight", true);
			else
				mAnimator->Play(L"PawOutroLeft", true);
			mOwnerCat->SetPawBack();
			Camera::SetShake(false);
		}
	}

	void Paw::Release()
	{
		mAnimator->Release();
	}

}