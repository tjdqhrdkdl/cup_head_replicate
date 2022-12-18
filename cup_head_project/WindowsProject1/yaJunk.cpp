#include "yaJunk.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"


namespace ya
{
	Junk::Junk(bool right, bool pink)
		:mAliveTime(5)
		,mAliveTimeChecker(0)
	{
		mPink = pink;
		SetName(L"Mouse_Junk");
		SetScale({ 50,50 });

		Collider* col = new Collider();
		AddComponent(col);

		mAnimator = new Animator();
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"BoltLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Bolt\\mouse_catapult_bolt_00", 5, 0.07f, false, false);
		mAnimator->CreateAnimation(L"BoltRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Bolt\\mouse_catapult_bolt_00", 5, 0.07f, false, true);
		mAnimator->CreateAnimation(L"CoinLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Coin\\mouse_catapult_coin_00", 5, 0.07f, false, false);
		mAnimator->CreateAnimation(L"CoinRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Coin\\mouse_catapult_coin_00", 5, 0.07f, false, true);
		mAnimator->CreateAnimation(L"GumLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Gum\\mouse_catapult_gum_00", 5, 0.07f, false, false);
		mAnimator->CreateAnimation(L"GumRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Gum\\mouse_catapult_gum_00", 5, 0.07f, false, true);
		mAnimator->CreateAnimation(L"NutLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Nut\\mouse_catapult_nut_00", 5, 0.07f, false, false);
		mAnimator->CreateAnimation(L"PopcapLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Popcap\\mouse_catapult_popcap_00", 5, 0.07f, false, false);
		mAnimator->CreateAnimation(L"ToothLeft", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Tooth\\mouse_catapult_tooth_00", 5, 0.07f, false, false);
		mAnimator->CreateAnimation(L"NutRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Nut\\mouse_catapult_nut_00", 5, 0.07f, false, true);
		mAnimator->CreateAnimation(L"PopcapRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Popcap\\mouse_catapult_popcap_00", 5, 0.07f, false, true);
		mAnimator->CreateAnimation(L"ToothRight", L"..\\Resources\\Image\\Werner Werman\\Phase 1\\Junk\\Tooth\\mouse_catapult_tooth_00", 5, 0.07f, false, true);
		if (!mPink)
		{
			if (right)
			{
				switch (rand()%5)
				{
				case 0:
					mAnimator->Play(L"BoltRight", true);
					break;
				case 1:
					mAnimator->Play(L"CoinRight", true);
					break;
				case 2:
					mAnimator->Play(L"ToothRight", true);
					break;
				case 3:
					mAnimator->Play(L"NutRight", true);
					break;
				case 4:
					mAnimator->Play(L"PopcapRight", true);
					break;
				}
			}
			else
			{
				switch (rand() % 5)
				{
				case 0:
					mAnimator->Play(L"BoltLeft", true);
					break;
				case 1:
					mAnimator->Play(L"CoinLeft", true);
					break;
				case 2:
					mAnimator->Play(L"ToothLeft", true);
					break;
				case 3:
					mAnimator->Play(L"NutLeft", true);
					break;
				case 4:
					mAnimator->Play(L"PopcapLeft", true);
					break;
				}
			}
		}
		else
		{
			if (right)
				mAnimator->Play(L"GumRight", true);
			else
				mAnimator->Play(L"GumLeft", true);
		}
	}

	Junk::~Junk()
	{
	}

	void Junk::Tick()
	{
		GameObject::Tick();
		mAliveTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
		}

		Vector2 pos = GetPos();
		pos += mDestDir * 800 * Time::DeltaTime();
		SetPos(pos);

		if (mParried)
			ObjectManager::Destroy(this);
	}

	void Junk::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Junk::OnCollisonEnter(Collider* other, Collider* my)
	{
	}

	void Junk::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Junk::OnCollisonExit(Collider* other, Collider* my)
	{
	}

	void Junk::Release()
	{
	}

}