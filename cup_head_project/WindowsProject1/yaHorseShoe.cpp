#include "yaHorseShoe.h"
#include "yaAnimator.h"
#include "yaTime.h"
#include "yaCollider.h"
#include "yaGround.h"
#include "yaObjectManager.h"
#include "yaBeppiPhaseThree.h"
namespace ya
{
	HorseShoe::HorseShoe(bool yellow, bool right, bool pink)
		:mbDropSoon(false)
		,mAliveTime(10)
		,mAliveTimeChecker(0)
	{
		mbYellow = yellow;
		mbRight = right;
		mPink = pink;

		mDir = Vector2::Up;
		SetName(L"HorseShoe");
		SetScale({ 60,60 });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"YellowIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horseshoes\\HorseShoe_Gold_", 16, 0.03f, true, false);
		mAnimator->CreateAnimation(L"YellowDrop", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horseshoes\\HorseShoe_Gold2_", 8, 0.1f, true, false);
		mAnimator->CreateAnimation(L"GreenIdle", L"..\\Resources\\Image\\Beppi\\Phase 2\\Phase 3\\Horseshoes\\HorseShoe_Green_", 16, 0.05f, true, false);

		if (mbYellow)
			mAnimator->Play(L"YellowIdle", true);
		else
			mAnimator->Play(L"GreenIdle", true);

	}

	HorseShoe::~HorseShoe()
	{
	}

	void HorseShoe::Tick()
	{
		GameObject::Tick();
		mAliveTime += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
			ObjectManager::Destroy(this);
		if (mOwnerBeppi->IsDropShoes() && !mbDropSoon)
		{
			mbDropSoon = true;
			mDropTimeChecker = (rand() % 5) * 0.1;
		}
		if (mbDropSoon)
		{
			mDropTimeChecker -= Time::DeltaTime();
			if (mDropTimeChecker <= 0)
				mbDrop = true;
		}
		Move();
	}

	void HorseShoe::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void HorseShoe::Move()
	{
		Vector2 pos = GetPos();
		if (mbYellow)
		{
			if (!mbStop)
			{
				if (mbRight)
				{
					if (mbComeBack)
					{
						pos.x -= 1200 * Time::DeltaTime();
						if (mStopXPos > pos.x)
							mbStop = true;
					}
					else
					{
						pos.x += 1200 * Time::DeltaTime();
						if (pos.x > 1800)
						{
							mbComeBack = true;
							pos.y -= 300;
						}
					}
				}
				else
				{
					if (mbComeBack)
					{
						pos.x += 1200 * Time::DeltaTime();
						if (mStopXPos < pos.x)
							mbStop = true;
					}
					else
					{
						pos.x -= 1200 * Time::DeltaTime();
						if (pos.x < -200)
						{
							mbComeBack = true;
							pos.y -= 300;
						}
					}
				}
			}
			else
			{
				if (mbDrop)
				{
					pos.y += 1000 * Time::DeltaTime();
					if(mAnimator->GetName()!=L"YellowDrop")
						mAnimator->Play(L"YellowDrop", false);
				}
			}
		}
		else
		{
			mSpeed = 700;
			if (mbDirChange)
				mDegree -= 200 * Time::DeltaTime();
			else
				mDegree += 200 * Time::DeltaTime();

			if (!mbDirChange && mDegree > 180)
				mbDirChange = true;
			else if (mbDirChange && mDegree < 0)
				mbDirChange = false;

			if (mbRight)
			{
				pos += math::Rotate(mDir, mDegree) * mSpeed * Time::DeltaTime();
			}
			else
			{
				pos -= math::Rotate(mDir, mDegree) * mSpeed * Time::DeltaTime();
			}
		}



		SetPos(pos);
	}

	void HorseShoe::OnCollisonEnter(Collider* other, Collider* my)
	{
		if (
			other->GetOwner()->GetLayer() == eColliderLayer::FrontObject
			&& dynamic_cast<Ground*>(other->GetOwner()) != nullptr
			&& mbYellow
			)
		{
			ObjectManager::Destroy(this);
		}
	}

	void HorseShoe::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void HorseShoe::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void HorseShoe::Release()
	{
		mAnimator->Release();
	}

}