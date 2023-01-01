#include "yaBoomerang.h"
#include "yaAnimator.h"
#include "yaCollider.h"
#include "yaObjectManager.h"
#include "yaTime.h"

namespace ya
{
	Boomerang::Boomerang()
		:mAliveTime(20)
		, mAliveTimeChecker(0)

	{
		SetName(L"Boomerang");
		SetScale({ 150.0f, 100.0f });
		AddComponent(new Collider());
		mAnimator = new Animator();
		AddComponent(mAnimator);
		mAnimator->CreateAnimation(L"Idle", L"..\\Resources\\Image\\Cagney Carnation\\Creating Object\\Boomerang\\Boomerang_", 9, 0.03f, false, false);

		mAnimator->Play(L"Idle", true);
	}

	Boomerang::~Boomerang()
	{
	}

	void Boomerang::Tick()
	{
		GameObject::Tick();
		mAliveTimeChecker += Time::DeltaTime();
		mGoTimeChecker += Time::DeltaTime();
		if (mAliveTimeChecker > mAliveTime)
		{
			ObjectManager::Destroy(this);
		}

		Vector2 pos = GetPos();
		if (mGoTimeChecker > 1)
		{
			if (mbGoRight)
			{
				pos.x += Time::DeltaTime() * 700;
			}
			else
			{
				pos.x -= Time::DeltaTime() * 700;
				if (pos.x < -300)
				{
					pos.y += 300;
					mbGoRight = true;
				}
			}
			SetPos(pos);
		}
	}

	void Boomerang::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Boomerang::OnCollisonEnter(Collider* other, Collider* my)
	{

	}

	void Boomerang::OnCollisonStay(Collider* other, Collider* my)
	{
	}

	void Boomerang::OnCollisonExit(Collider* other, Collider* my)
	{
	}


	void Boomerang::Release()
	{
	}

}