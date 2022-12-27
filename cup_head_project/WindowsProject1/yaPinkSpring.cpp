#include "yaPinkSpring.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaTime.h"
#include "yaGround.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaWernerWermanPh1.h"
#include "yaObjectManager.h"
namespace ya
{
	PinkSpring::PinkSpring(float degree, bool right)
	{
		mbRight = right;
		mDegree = degree;
		SetName(L"PinkSpring");
		SetScale({ 100.0f,60.0f });
		mPink = true;
		mEmptyPink = true;

		Collider* col = new Collider();
		col->SetDanger(false);
		AddComponent(col);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"FlipLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Spring\\Flip\\mouse_spring_flip_00", 7, 0.04f, false, false);
		mAnimator->CreateAnimation(L"FlipRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Spring\\Flip\\mouse_spring_flip_00", 7, 0.04f, false, true);
		mAnimator->CreateAnimation(L"Land", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Spring\\Land\\mouse_spring_land_00", 12, 0.04f, false, false);
		mAnimator->CreateAnimation(L"Launch", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Spring\\Launch\\mouse_spring_launch_00", 12, 0.04f, false, false);
		mAnimator->CreateAnimation(L"Boil", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Spring\\Boil\\mouse_spring_boil_00", 5, 0.08f, false, false);
		mAnimator->CreateAnimation(L"Death", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Spring\\Death\\mouse_spring_death_00", 16, 0.04f, false, false);

		mAnimator->GetCompleteEvent(L"Launch") = std::bind(&PinkSpring::LandCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Death") = std::bind(&PinkSpring::DeathCompleteEvent, this);

		if (right)
			mAnimator->Play(L"FlipRight", true);
		else
			mAnimator->Play(L"FlipLeft", true);

	}

	PinkSpring::~PinkSpring()
	{
	}

	void PinkSpring::Tick()
	{
		Vector2 pos = GetPos();

		if (mAnimator->GetPlayAnimation()->GetName() == L"FlipLeft" or mAnimator->GetPlayAnimation()->GetName() == L"FlipRight")
		{
			mDegree -= 90 * Time::DeltaTime();
			if (mDegree < -160)
				mDegree = -160;
			if (mbRight)
			{
				pos.x -= math::Rotate(Vector2::Up, mDegree).x * 650 * Time::DeltaTime();
				pos.y += math::Rotate(Vector2::Up, mDegree).y * 650 * Time::DeltaTime();
			}
			else
			{
				pos += math::Rotate(Vector2::Up, mDegree) *650 * Time::DeltaTime();
			}
		}
		SetPos(pos);
		GameObject::Tick();
	}

	void PinkSpring::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PinkSpring::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (dynamic_cast<Ground*>(other->GetOwner()) != nullptr)
		{
			Vector2 pos = GetPos();
			pos.y = 750;
			SetPos(pos);
			mAnimator->Play(L"Land", false);
		}

		else if (dynamic_cast<Player*>(other->GetOwner()) != nullptr)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (player->IsParrying())
			{
				if (mAnimator->GetPlayAnimation()->GetName() != L"FlipLeft" && mAnimator->GetPlayAnimation()->GetName() != L"FlipRight")
				{
					mAnimator->Play(L"Launch", false);
				}
			}
		}

		else if (dynamic_cast<WernerWermanPh1*>(other->GetOwner()) != nullptr)
		{
			WernerWermanPh1* boss = dynamic_cast<WernerWermanPh1*>(other->GetOwner());
			if (boss->IsDashing())
			{
				GetComponent<Collider>()->SetOff(true);
				mAnimator->Play(L"Death", false);
			}
		}
	}

	void PinkSpring::OnCollisonStay(Collider* other, Collider* my)
	{
		if (dynamic_cast<Player*>(other->GetOwner()) != nullptr)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (player->IsParrying())
			{
				if (mAnimator->GetPlayAnimation()->GetName() != L"FlipLeft" && mAnimator->GetPlayAnimation()->GetName() != L"FlipRight")
				{
					mAnimator->Play(L"Launch", false);
				}
			}
		}
		else if (dynamic_cast<WernerWermanPh1*>(other->GetOwner()) != nullptr)
		{
			WernerWermanPh1* boss = dynamic_cast<WernerWermanPh1*>(other->GetOwner());
			if (boss->IsDashing())
			{
				GetComponent<Collider>()->SetOff(true);
				mAnimator->Play(L"Death", false);
			}
		}
	}

	void PinkSpring::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void PinkSpring::LandCompleteEvent()
	{
		mAnimator->Play(L"Boil", true);
	}

	void PinkSpring::DeathCompleteEvent()
	{
		ObjectManager::Destroy(this);
	}

	void PinkSpring::Release()
	{
		mAnimator->Release();
	}

}